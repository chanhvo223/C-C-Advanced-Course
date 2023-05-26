#include "multiples_parameters.h"

void sum(int count, ...)
{
    double result = 0.0;

    // Create 2 ptr for double and int data types
    va_list ptr_double, ptr_int;

    va_start(ptr_int, count);
    va_start(ptr_double, count);

    for (int i = 0; i < count; i++)
    {
        // All values with double will be 0
        int value_int = va_arg(ptr_int, int);
        printf("value int: %d\n", value_int);
        result = result + value_int;
    }

    for (int i = 0; i < count; i++)
    {
        // All values with int will be 0
        double value_double = va_arg(ptr_double, double);
        printf("value double: %f\n", value_double);
        result = result + value_double;
    }

    va_end(ptr_int);
    va_end(ptr_double);
    printf("Sum = %f", result);
}