#ifndef __STACK_H__
#define __STACK_H__

#include "main.h"

#define true 1
#define false 0
#define bool int

#define STACK_SIZE 10

typedef struct
{
    int top;
    void *data[STACK_SIZE];

    void (*push)(struct Stack *top, void *value);
    int (*pop)(struct Stack *stack);
    void (*empty)(struct Stack *stack);
} Stack;

void stackInit(Stack *stack);

#endif