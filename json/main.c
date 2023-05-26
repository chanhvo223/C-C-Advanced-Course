#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>


typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

char *nameJson[] = {"JSON_NULL",
                    "JSON_BOOLEAN",
                    "JSON_NUMBER",
                    "JSON_STRING",
                    "JSON_ARRAY",
                    "JSON_OBJECT"};

typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            struct JsonValue *values;
            size_t count;
        } array;
        struct {
            char **keys;
            struct JsonValue *values;
            size_t count;
        } object;
    } value;
} JsonValue;



JsonValue *parse_json(const char **json);

void free_json_value(JsonValue *json_value);

static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}

JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}

JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}

JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;
    double num = strtod(*json, &end);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

JsonValue *parse_string(const char **json) {
    skip_whitespace(json);
    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start;
            char *str = (char *) malloc(length + 1);
            strncpy(str, start, length);
            str[length] = '\0';
            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json);
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_json(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}


JsonValue *parse_json(const char **json) {
    while (isspace(**json)) {
        (*json)++;
        printf("ky tu: %x\n", **json);
    }

    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:
            if (isdigit(**json) || **json == '-') {
                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}



////////////

char *generate_json(const JsonValue *json_value);

void grow_buffer(char **buffer, size_t *buffer_size, size_t needed) {
    if (*buffer_size < needed) {
        *buffer_size = needed * 2;
        *buffer = realloc(*buffer, *buffer_size);
    }
}

void generate_null(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    grow_buffer(buffer, buffer_size, 5);
    strcpy(*buffer, "null");
}

void generate_boolean(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    const char *bool_str = json_value->value.boolean ? "true" : "false";
    size_t len = strlen(bool_str);
    grow_buffer(buffer, buffer_size, len + 1);
    strcpy(*buffer, bool_str);
}

void generate_number(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    char num_str[64]; // buffer tạm thời cho số
    snprintf(num_str, sizeof(num_str), "%.17g", json_value->value.number);
    size_t len = strlen(num_str);
    grow_buffer(buffer, buffer_size, len + 1);
    strcpy(*buffer, num_str);
}

void generate_string(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    const char *str = json_value->value.string;
    size_t len = strlen(str);
    grow_buffer(buffer, buffer_size, len + 3);
    snprintf(*buffer, *buffer_size, "\"%s\"", str);
}

void generate_array(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    grow_buffer(buffer, buffer_size, 2);
    (*buffer)[0] = '[';
    (*buffer)[1] = '\0';
    for (size_t i = 0; i < json_value->value.array.count; i++) {
        char *item_str = generate_json(&json_value->value.array.values[i]);
        size_t len = strlen(item_str);
        grow_buffer(buffer, buffer_size, *buffer_size + len + 2);
        strcat(*buffer, item_str);
        free(item_str);
        if (i < json_value->value.array.count - 1) {
            strcat(*buffer, ",");
        }
    }
    strcat(*buffer, "]");
}

void generate_object(const JsonValue *json_value, char **buffer, size_t *buffer_size) {
    grow_buffer(buffer, buffer_size, 2);
    (*buffer)[0] = '{';
    (*buffer)[1] = '\0';
    for (size_t i = 0; i < json_value->value.object.count; i++) {
        const char *key = json_value->value.object.keys[i];
        char *value_str = generate_json(&json_value->value.object.values[i]);
        size_t len = strlen(key) + strlen(value_str) + 4;
        grow_buffer(buffer, buffer_size, *buffer_size + len + 1);
        strcat(*buffer, "\"");
        strcat(*buffer, key);
        strcat(*buffer, "\":");
        strcat(*buffer, value_str);
        free(value_str);
        if (i < json_value->value.object.count - 1) {
            strcat(*buffer, ",");
        }
    }
    strcat(*buffer, "}");
}



// Hàm chính để tạo chuỗi JSON từ cấu trúc JsonValue
char *generate_json(const JsonValue *json_value) {
    char *buffer = NULL;
    size_t buffer_size = 0;

    if (json_value == NULL) {
        return NULL;
    }

    switch (json_value->type) {
        case JSON_NULL:
            generate_null(json_value, &buffer, &buffer_size);
            break;
        case JSON_BOOLEAN:
            generate_boolean(json_value, &buffer, &buffer_size);
            break;
        case JSON_NUMBER:
            generate_number(json_value, &buffer, &buffer_size);
            break;
        case JSON_STRING:
            generate_string(json_value, &buffer, &buffer_size);
            break;
        case JSON_ARRAY:
            generate_array(json_value, &buffer, &buffer_size);
            break;
        case JSON_OBJECT:
            generate_object(json_value, &buffer, &buffer_size);
            break;
        default:
            break;
    }

    return buffer;
}



/////////////

void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}



void test(JsonValue* json_value){
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        size_t num_fields2 = json_value->value.object.values->value.object.count;
        for (size_t i = 0; i < num_fields; ++i) {

            char* key = json_value->value.object.keys[i];
            JsonValue* value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);

            //printf("type: %s\n", nameJson[type]);

            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }

            if(type == JSON_NUMBER){
                printf("%s: %f\n", key, value->value.number);
            }

            if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }

            if(type == JSON_OBJECT){
                printf("%s: \n", key);
                test(value);
            }

            if(type == JSON_ARRAY){
                printf("%s: \n", key);
                
                for (int i = 0; i < value->value.array.count; i++)
                {
                  
                    test(&value->value.array.values[i]);
                }
                
            }

  
        }

     
    }
}



int main(int argc, char const *argv[])
{
     // Chuỗi JSON đầu vào
    const char* json_str = "{\"Ten\":\"Nguyen A\",\"Tuoi\":20,\"Diachi\":{\"Phuong_Xa\":\"Phuong 6\",\"Tinh_Tp\":\"HCM\"}}";
    

    // Phân tích cú pháp chuỗi JSON
    JsonValue* json_value = parse_json(&json_str);

    test(json_value);

    // Kiểm tra kết quả phân tích cú pháp

       // Giải phóng bộ nhớ được cấp phát cho JsonValue
        free_json_value(json_value);
    
    return 0;
}
