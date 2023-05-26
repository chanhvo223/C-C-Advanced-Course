#include "stack.h"

static bool isFull(Stack *stack)
{
    return stack->top == (STACK_SIZE - 1);
}

static void push(Stack *stack, void *value)
{
    if (isFull(stack))
    {
        printf("isFull\n");
    }
    else
    {
        stack->top++;
        stack->data[stack->top] = value;
    }
}

static bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

static void pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("isEmpty\n");
    }
    else
    {

        free(stack->data[stack->top]);

        stack->data[stack->top] = NULL;

        stack->top--;
    }
}

static void empty(Stack *stack)
{
    for (size_t i = 0; i < STACK_SIZE; i++)
    {
        pop(stack);
    }
}

void stackInit(Stack *stack)
{
    for (size_t i = 0; i < STACK_SIZE; i++)
    {
        stack->data[i] = NULL;
    }

    stack->top = -1;
    stack->push = &push;
    stack->pop = &pop;
    stack->empty = &empty;
}