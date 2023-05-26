#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "main.h"

#define bool int
#define true 1
#define false 0

#define INIT_QUEUE_SIZE -1

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

/// @brief The queue, front stores the front node of LL and rear stores the last node of LL
typedef struct Queue
{
    Node *front, *rear, *lastNode;
    int size, capacity;

    int (*deQueue)(struct Queue *);
    void (*enQueue)(struct Queue *, int);
    int (*frontQueue)(struct Queue *);
    int (*rearQueue)(struct Queue *);
} Queue;

void queueInit(Queue *queue, int capacity);

#endif