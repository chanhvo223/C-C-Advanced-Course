# Compiler gcc IDE/EDITOR 
## COMPILER
Dịch từ ngôn ngữ do lập trình viên viết (C/C++, PHP, HTML, ) sang ngôn ngữ máy.

Từ file `main.c/cpp, main.h`,... nó **preprocess** sang file `main.i` từ đây các MACRO hay include sẽ được thêm vào `main.i`.

Sau đó `main.i` sẽ được compiler dịch sang file `main.s` dưới dạng assembly.

=> được assembler sang file object.

=> Linker tạo ra exucutable file. `main.exe`

## IDE/EDITOR
IDE: Phần mềm + compiler 

Vd: devC, mấy cái ấn cái là chạy.

Editor: lưu code.

# MACRO

Trong quá trình tiền xử lý, tất cả các chữ được `#define` sẽ thay thế vào.
VD: file main.c
```c
#define MAX_ARR_LENGTH 100

int a[MAX_ARR_LENGTH];

int main(){
    printf("MAX_ARR_LENGTH: %d", MAX_ARR_LENGTH);
    return 0;
}
```

Sau quá trình tiền xử lý, nó sẽ thay thế **tất cả** các chữ `MAX_ARR_LENGTH` bằng `100`, trong file `main.i` sẽ như sau:
```c
int a[100];

int main(){
    printf("MAX_ARR_LENGTH: %d", 100);
    return 0;
}
```

## #if #endif

```c
#define BLUETOOTH A24

#if BLUETOOTH == 0

a = 2;

#elif BLUETOOTH == 1

a = 3;

#else

a = 4;

#endif

```

## Truyền tham số

Dùng `##` để nối chuổi trong MACRO 
```c
#define typeVar(type, name) type var_##name

```
nếu `name = a` thì `var_##name` sẽ là `var_a`

Có thể định nghĩ nhiều dòng bằng `\`

```c
#define typeVar(type, name) type var_##name\
                            type var1_##name\
                            type var2_##name

```

## Define 1 hàm
## Cấu trúc đặt tên 
Có 2 files: 1 header và 1 source.

VD: `knight.h` và `knight.cpp` 

## Tránh define trùng

```cpp
#ifndef __KNIGHT_H // Cái tên này chỉ đặt tránh trùng với các thư viện khác.
#define __KNIGHT_H

#endif
```

# Multiples parameters in function

```c
int sum(int number_of_sum, ...){
    int sum = 0;
    va_list ptr;
    va_start(ptr, number_of_sum);
    for(int i = 0; i < number_of_sum; i++){
        sum += sum + va_arg(ptr, int);
                //  va_arg(ptr, int)
                // -------------^--- Kiểu dữ liệu của cái `...`
                // Gọi lần 1 thì in ra thằng đầu tiên, gọi lần 2 thì ra input thứ 2
    }
    va_end(ptr);
}
```

- BTVN1: `sum(3, 1, 2, 5.2);`
Tính cổng mà có nhiểu kiểu dữ liệu vừa `int` vừa `double`
- BTVN2: input nhiều hơn số lượng cần thiết `sum(100, 1, 2, 3.2);` nhưng vẫn ra `sum` đúng.

# Variables types (volatile, register, static, auto)

## `static` 

### `static` vs `normal` and `auto`

Biến `static` tồn tại cho đến khi **hết vòng đời** của chương trình. Nó sẽ không bị mất khi kết thúc lời gọi hàm.

VD:
```c
#include <stdio.h>

void count(){
    int count = 0;      // Biến bình thường
    printf("count: %d\n",count);
    count = count + 1;
}

int main() {
    count(); // output: count = 0
    /*
        1. Khởi tạo biến count ở địa chỉ nào đó trên vùng nhớ.
        2. In giá trị nó ra.
        3. Cộng giá trị ở vùng nhớ đó lên 1 -> vô nghĩa vì
        4. Giải phóng địa chỉ của biến count.
        Tương tự cho những lời gọi hàm ở dưới.
    */

    count(); // output: count = 0


    count(); // output: count = 0
    return 0;
}
```

Ở vd khác.
```c
#include <stdio.h>

void count(){
    static int count = 0;      // Biến static
    printf("count: %d\n",count);
    count = count + 1;
}

int main() {
    count(); // output: count = 0
    /*
        1. Khởi tạo biến count ở địa chỉ nào đó trên vùng nhớ.
        2. In giá trị nó ra.
        3. Cộng giá trị ở vùng nhớ đó lên 1
        4. Không giải phóng vùng nhớ ở Stack vì static là khởi tạo ở "data segment"
        Tương tự cho những lời gọi hàm ở dưới.
    */

    count(); // output: count = 1


    count(); // output: count = 2
    return 0;
}
```

### `static` được gọi trong hàm **chỉ có nghĩa trong hàm** đó.
```c
#include <stdio.h>

void count(){
    static int count = 0;      // Biến static
    printf("count: %d\n",count);
    count = count + 1;
}

int main() {
    count(); // output: count = 0

    printf("count: %d\n",count); // output: lỗi vì không biết count là thằng nào.
    count(); // output: count = 1

    count(); // output: count = 2
    return 0;
}
```
Cho nên ta sử dụng 1 con trỏ để truy câp vào địa chỉ đó.
```c
#include <stdio.h>

int *ptr;

void count(){
    static int count = 0;      // Biến static
    ptr = &count;
    printf("count: %d\n",count);
    count = count + 1;
}

int main() {
    count();    // output: count = 0
    
    *ptr = 100;
    count();    // output: count = 100
    
    count();    // output: count = 101
    
    return 0;
}
```

## `volatile`

Vấn đề là khi đọc chân ở một số vdk thì quá trình compiler nó sẽ tự tối ưu hóa một biến mà đọc đi đọc lại nhiều lần. (1 chân của vdk).

Và vì khí nó tối ưu hóa như vậy nên khi đọc giá trị từ 1 chân nó chỉ xuất 1 giá trị (không đúng đối với trường hợp vdk).

Nên khi đó từ khóa volatile sẽ bắt buộc compiler ghi đè và nói rằng "đừng có tối ưu hóa biến này, hãy đọc chân của vdk đó 1 lần nữa".

Cách khai báo:
```c
volatile int PIN01;
```
## `register`

Cấu trúc của 1 con vdk như sau, hãy quan tâm tới 3 vị trí CPU, RAM và Register.

![register](docs/register.png)

Khi tạo một biến bình thường.
```c
int a = 0;              // Lưu vào RAM.
register int b = 0;     // Lưu vào Register

```

Nhìn vào sơ đồ ta thấy vị trí của `register` gần hơn RAM đối với CPU. Nên khi truy suất dữ liệu. Dữ liệu được lưu vào `register` sẽ được lấy nhanh hơn RAM.


## `extern`

Truy cập biến cục bộ từ 1 file khác.

# `struct` & `union`

`struct` và `union` là kiểu dữ liệu mà người dùng tự định nghĩa.

## Tuy nhiên với `struct` thì nó phân từng phần tử sẽ có địa chỉ riêng.

```c
struct data {
  char uid;
  char uid_data;
};

int main(int argc, char const *argv[]) {
    struct data test01;
    
    printf("Dia chi cua uid: %p\n", &test01.uid);             
    printf("Dia chi cua uid_data: %p\n", &test01.uid_data);  
    /*
    OUTPUT:
    Dia chi cua uid: 0x7ffd6e357898
    Dia chi cua uid_data: 0x7ffd6e357899
    Vì phần tử đầu tiên của struct cũng là địa chỉ của struct, vì phần tử đầu tiên là 1 byte (kiểu chữ liệu char) nên địa chỉ tiếp theo của uid_data sẽ là địa chỉ của uid + 1 byte.
    */
    return 0;
}

```
## `union` sẽ là cùng 1 địa chỉ.

```c
union data {
  char uid;
  char uid_data;
};

int main(int argc, char const *argv[]) {
  union data test01;

  printf("Dia chi cua uid: %p\n", &test01.uid);
  printf("Dia chi cua uid_data: %p\n", &test01.uid_data);
  /*
  OUPUT:
  Dia chi cua uid: 0x7ffed8f00377
  Dia chi cua uid_data: 0x7ffed8f00377
  */
  return 0;
}

```

## Ứng dụng:

Ta lồng `struct` vào `union` để có thể truy xuất và gửi dữ liệu nhanh hơn.

```c
typedef union {
  struct {
    char uid[4];
    char data[8];
  } frame;

  char data_frame[12];
} frame_nfc;
```

Bằng cách này khi ta muốn gán dữ liệu cho `frame_nfc` một cách dễ dàng.

Nhưng khi gửi dữ liệu ta chỉ cần gửi 1 frame của nó đi là xong. Vì `struct frame` và `data_frame` có cùng 1 địa chỉ và cùng số bytes (12 bytes).

# `setjump.h`

Xét ví dụ:
```c
#include <setjmp.h>

jmp_buf buf;

int main() {
    int i;
    i = setjump(buf);

    printf("i: %d\n", i);

    if (i!=0){
        printf("i khac khong i: %d\n", i);
        exit(0);
    }

    longjump(buf, i); // set i = 1

    return 0;

}
```

```c
OUPUT: 
i: 0
i: 1
i khac khong i: 1
```

Giải thích:

Thì đầu tiên code chạy tới `setjump(buf)` sau đó nó nhảy xuống `longjump(buf, 1)` và set giá trị của `i = 1` (kì diệu vcl).

Sau đó nó mới thực thi chương trình ở dưới dòng `i = setjump(buf);`

## `setjump` vs `goto`

`goto` chỉ áp dụng trong **hàm**, trong khi `setjump` có thể sử dụng **toàn cục**.

## Ứng dụng `setjump`

Áp dụng nhấn external interupt (nút nhấn) không cần xử lý qua timer (một cách khác).


# bitmask

## Clear bit 0 -> 1
`0101.0101`

and operator (&) truth table:

| x   | y   | x AND y (x \| y) |
| --- | --- | :--------------: |
| 0   | 0   |        0         |
| 0   | 1   |        0         |
| 1   | 0   |        0         |
| 1   | 1   |        1         |

Xóa bit số 5.

Để xóa bit số 5 ta làm như sau:

        0101.0101
    and 1110.1111
        0100.0101 -> bit số 5 đã xóa.

Vậy `1110.1111` là `~(1 << n)` với n là số bit cần xóa.

## Set bit 1 -> 0
`0101.0101`

or operator (|) truth table:

| x   | y   | x OR y (x \| y) |
| --- | --- | :-------------: |
| 0   | 0   |        0        |
| 0   | 1   |        1        |
| 1   | 0   |        1        |
| 1   | 1   |        1        |

set bit số 4 = 1:

        0101.0101
    or  0000.1000
        0101.1101 -> set được bit số 4 = 1

set bit ta làm như sau: `|= (1 << n)` với n là số bit cần set.


## Toggle bit (if 0 ? 1 : 0)


XOR operator (^) truth table:

| x   | y   | x XOR y (x \^ y) |
| --- | --- | :--------------: |
| 0   | 0   |        0         |
| 0   | 1   |        1         |
| 1   | 0   |        1         |
| 1   | 1   |        0         |


`0101.0101`

Bật tắt bit thứ 4:
```c
    0101.0101
XOR 0001.0000
    0100.0101
-------^---------- 1 XOR 1 = 0
```

```c
    0100.0101
XOR 0001.0000
    0101.0101
-------^---------- 0 XOR 1 = 1
```
Để bật tắt bit thứ k của n thì: `n ^= 1 << k;`
# Con trỏ Pointer

## Khởi tạo con trỏ

`<kiểu dữ liệu> * <tên con trỏ>;`

```c
int *ptr_int; // Khao báo con trỏ int
double *ptr_double;
char *ptr_char;

(int*) * prt_prt_int; // Kiểu dữ liệu int*
(int**) * ptr_prt_prt_int; // Kiểu dữ liệu int**

```

## Con trỏ hàm

Mỗi hàm khi khai báo đều có 1 địa chỉ
### Khai báo con trỏ

Ví dụ: ta có nhiều hàm có cùng kiểu input vào output.

`void (<Địa chỉ hàm>)(parameters);`

```c

void tong(int a, int b);
void hieu(int a, int b);
void tich(int a, int b);
double thuong(int a, int b);

int main(){
    //Khai báo con trỏ hàm cùng kiểu dữ liệu với các hàm mà ta sẽ trỏ vào.
    void (*ptr_ham)(int, int);
    double (*ptr_double_ham)(int, int);

    ptr_ham = &tong; // Gan dia chi cua ptr_ham = dia chi cua tong.
    ptr_double_ham = &thuong;

    ptr_double_ham(5, 6);
    ptr_ham(12, 5);
}

```

Ví dụ khác: Parameter là địa chỉ của một hàm khác (scheduler, interupt)

```c
void calc(int a, int b, void (*fnc_prt)(int, int));
//--------^------^------^--------------------------
//        para1  para2  Địa chỉ của hàm.
```

Ví dụ khác.

```c
typedef struct{
    int a; 
    int b; 
    void (*fnc_prt)(int, int);
}calc;

calc tinh_tong = (5, 6, &tong);
```

# Con trỏ `void`

Ta có 3 kiểu dữ liệu 
```c
int a  = 4;
double b = 4.1;
char c = 'A';

int sum(int a, int b);
```

Con trỏ void có thể trỏ tới **bất cứ** kiểu dữ liêu nào

```c
void (* void_pointer);

void_pointer = &a;
void_pointer = &b;
void_pointer = &c;
void_pointer(int, int) = &sum;

```

## Mảng con trỏ
```c
// mảng bình thường 
int arr[] = {1,2,3,4,5,6,7};
char arr_char[] = {'a', 'b', 'c', 'd', 'e'};
double arr_double[] = {3.14, 3.14, 3.14, 3.14, 3.14};

void sum(int a, int b);
void minus(int a, int b);

void (* funcArr[])(int a, int b) = {&tong, &hieu};
// Khai báo mảng địa chỉ arr

void *arr[5] = {arr, arr_char, arr_double};

BTVN sử dụng các biến, hàm ở trên thông qua mảng địa chỉ.


```

# Con trỏ NULL
## KICH THƯỚC CON TRỎ PHỤ THUỘC VÀO VI XỬ LÝ.

VXL 32 bit / 8 = 4 bytes.\
VXL 64 bit / 8 = 8 bytes.

## Khi khai báo con trỏ, NÊN cho nó một giá trị NULL trước.

`void *ptr = NULL;`

Và sau khi sử dụng ptr xong thì ta gán lại bằng giá trị NULL

# Linked list

Cấu trúc của linked-list nó khác với array là linked-list là mảng động. 

```c
typedef struct {
    int data,
    node *next
} node;
```

# Viết theo tiêu chuẩn.
## Comment doxygen
Trước mỗi function đều phải có comment theo kiểu doxygen:
```c

/**
 * @brief initation a new Vector (Tóm tắt hàm này làm gì?)
 * 
 * @param vector (Thông số truyền vào là gì?)
 */
void vectorInit(Vector *vector)
{
    vector->value = 0;
    vector->next = NULL;
    vector->pushBack = &pushBack;
}
```
## Đặt tên hàm
<động từ> trước.
```c
void pushBack(Vector *vector);
void popBack(Vector *vector);
```

## Cấu trúc file thư mục dự án của c
```
projectName
    - Header (chứa file .h) 
        linkedList.h
        main.h
    - Source (chứa file .c)
        linkedlist.c
        main.c
```

# Viết như thư viện.

Tạo một kiểu dữ liệu vector.
```c
typedef struct {
    void (*push_back)(node *, int);
    void (*erase)(node *, int);
    node *node;
}vector;
```
Tạo một hàm Init như một contructor.
```c
void vectorInit(node **node){
    
}


```
# Makefile


# Json
## Cấu trúc file .json
```json
{
    "Object01": {
        "KEY01": "value",
        "KEY02": "value",
        "KEY03": "value",
        "Object01_01": {
            "KEY": "value",
            "KEY": "value",
        }
    },
    
    "Object02": {
        "KEY": "value",
        "KEY": "value",
        "KEY": "value",
        "Object02_01": {
            "KEY": "value",
            "KEY": "value",
        },
        "Object02_02": {
            "KEY": "value",
            "KEY": "value",
        }
    },
}
```
# Stack, Stack pointer, Program Counter (PC)

## Sơ lược Program Counter (PC)

1 thanh ghi là 4bytes (32bit).

PC là bộ đếm, nghĩa là nó sẽ đếm và tăng từng địa chỉ.

Mỗi địa chỉ là 32bit.

## Stack structure FILO
### i++ vs ++i
Giá trị trước đó và giá trị sử dụng:

`i++` là nó lấy giá trị cũ, và sau đó nó tăng lên 1 cho vòng lặp sau:
```c
int i = 0;
printf("%d\n", i++); // outputs 0
printf("%d\n", i);   // outputs 1
```

Đối với `++i` thì nếu giá trị trước đó là 3 nó sẽ tăng lên thành 4 **để chạy code**. Sau đó nó giữ nguyên giá trị `i = 4`

```c
int i = 0;
printf("%d\n", ++i); // outputs 1
printf("%d\n", i);   // outputs 1
```
## Câu hỏi:

1. Tại sao khi chạy, vdk vào hàm main chạy trước?

# Queue Structure FIFO
`Enqueue()` – Adds (or stores) an element to the end of the queue..

`Dequeue()` – Removal of elements from the queue.

`Peek()` or `front()`- Acquires the data element available at the front node of the queue without deleting it.

`rear()` – This operation returns the element at the rear end without removing it.

`isFull()` – Validates if the queue is full.

`isNull()` – Checks if the queue is empty.
![](docs/fifo.png)

# c++
## Function template
https://www.learncpp.com/cpp-tutorial/function-templates/

## OOP
### Class
Class hoạt động như một bản blueprint. Nó không có giác trị hay địa chỉ gì cả, cho đến khi ta khai báo.
### Public & Pirvate in class

### Constructor

Hàm chạy đầu tiên khi khởi tạo một object 

```cpp
class MyClass{
    public:
        ClassConstructor(int pro01, int pro02);
        void showClass();

    private:
        int property01;
        int property02;
}

Myclass::ClassConstructor(int pro01, int pro02){
    property01 = pro01;
    property02 = pro02;
}

```
### Static in class


### Hpp & Cpp, Cấu trúc class ở file header và source.


### Tính kế thừa (inheritance)
### Kế thừa public 


### Kế thừa private 

### Tính ghi đè.
