#include "main.h"

int main(int argc, char const *argv[])
{
    Stack a;
    stackInit(&a);
    for (int i = 0; i < 15; i++)
    {
        /* code */
        void *ptr = (void *)malloc(sizeof(void));

        printf("input %p to stack\n", ptr);

        a.push(&a, ptr);
    }

    a.empty(&a);

    for (int i = 0; i < STACK_SIZE; i++)
    {
        printf("a[%d]: %p\n", i, a.data[i]);
    }

    return 0;
}
