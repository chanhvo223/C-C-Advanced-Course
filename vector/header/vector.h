#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "main.h"

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct
{
    Node *node;
    void (*pushBack)(Node **, int);
    void (*getNode)(Node **, int);
    int (*size)(Node *);
    void (*clear)(Node **);
    void (*erase)(Node **head, int pos);
    void (*assign)(Node **head, int index, int value);
} Vector;

void vectorInit(Vector *vector);

#endif