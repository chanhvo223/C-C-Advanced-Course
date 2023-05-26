#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "main.h"

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node *createNote(int value);

void pushBack(Node **head, int value);

int getNode(Node **head, int node_number);

int size(Node *head);

#endif