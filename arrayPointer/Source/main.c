#include "main.h"

int main()
{
    int arr[] = {1, 3, 5, 7};
    char arr_char[] = {'a', 'b', 'c', 'd', 'e'};
    double arr_double[] = {3.141, 4.142, 5.143, 6.144, 7.145};
    void (*tongHieu[])(int a, int b) = {&tong, &hieu};
    void *arr_ptr[5] = {arr, arr_char, arr_double, tongHieu};

    printf("Lay kieu du lieu cua int\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", *((int *)arr_ptr[0] + i));
    }

    printf("Lay kieu du lieu cua char\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%c\n", *((char *)arr_ptr[1] + i));
    }

    printf("Lay kieu du lieu cua double\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%f\n", *((double *)arr_ptr[2] + i));
    }

    // access function tong through *arr_ptr
    ((void (*)(int, int))(((void **)(arr_ptr[3]))[0]))(3, 2);
    ((void (*)(int, int))(((void **)(arr_ptr[3]))[1]))(5, 2);

    return 0;
}