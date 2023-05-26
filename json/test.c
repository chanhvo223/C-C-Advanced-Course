#include <stdio.h>

/**
 * @brief Simple format print json string
 *
 * @param json_object
 */
void printJsonObject(char *json_object)
{
    // Loop all strings in json_object
    for (int i = 0; json_object[i] != '\0'; i++)
    {
        char c = json_object[i];
        switch (c)
        {
        case '{':
            printf("%c\n\t", c);
            break;
        case ',':
            printf("%c\n\t", c);
            break;
        case '}':
            printf("\n%c", c);
            break;
        default:
            printf("%c", c);
        }
    }
}

int main()
{
    char *json_object = "{\"ten\":\"Nguyen A\", \"tuoi\": \"19\", \"diachi\": \"HCM\"}";

    printJsonObject(json_object); // Print the JSON object with an initial indent of 0

    printf("\n"); // Print a newline character at the end

    return 0;
}
