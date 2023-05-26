#include "queue.h"

Node *createNode(int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

/**
 * @brief Check if the queue is empty
 *
 * @param q
 * @return int
 */
static int isEmpty(Queue *q)
{
    return (q->size == INIT_QUEUE_SIZE);
}

/**
 * @brief Remove the rear element from the queue and return the value
 *
 * @param queue
 * @return int
 */
static int deQueue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
    {
        queue->size--;
        Node *temp = queue->front;
        int value = temp->value;
        queue->front = queue->front->next;
        free(temp);

        // for safety
        temp = NULL;
        return value;
    }
}
/**
 * @brief Check if queue is Full
 *
 * @param queue
 * @return int
 */
static bool isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

/**
 * @brief Add new elements to the queue's rear
 *
 * @param queue
 * @param value
 */
static void enQueue(Queue *queue, int value)
{
    if (isFull(queue))
    {
        // If the queue is full, return overflow error and exit.
        printf("queue is Full\n");
    }
    else
    {

        queue->rear = createNode(value);

        // check if 1st element
        if (queue->front == NULL)
        {
            queue->front = queue->rear;

            queue->front->value = queue->rear->value;
            queue->size++;

            // optimize find the front.next == NULL
            queue->lastNode = queue->front;
            return;
        }

        /*
            Optimize the queue to find the front.next == NULL.
        */

        // Find front.next == NULL
        // while (queue->lastNode->next != NULL)
        // {
        //     queue->lastNode = queue->lastNode->next;
        // }

        // update front.next. This front.next is always NULL.
        queue->lastNode->next = queue->rear;

        // store lastNode = front's last node
        queue->lastNode = queue->lastNode->next;

        queue->size++;
    }
}

int front(Queue *queue)
{
    return queue->front->value;
}

int rear(Queue *queue)
{
    return queue->lastNode->value;
}

/**
 * @brief Initializes the queue with capacity
 *
 * @param queue
 * @param capacity
 */
void queueInit(Queue *queue, int capacity)
{
    queue->capacity = capacity;
    queue->size = INIT_QUEUE_SIZE;
    queue->front = NULL;
    queue->rear = NULL;
    queue->deQueue = &deQueue;
    queue->enQueue = &enQueue;
    queue->frontQueue = &front;
    queue->rearQueue = &rear;
}
