#include "main.h"

int main(int argc, char const *argv[])
{
    Queue q;
    queueInit(&q, 7);

    for (int value = 10; value < 20; value++)
    {
        q.enQueue(&q, value);
    }

    for (int i = 0; i <= q.capacity - 2; i++)
    {
        printf("Queue No. %d: %d\n", i, q.deQueue(&q));
    }


    printf("Queue front value: %d\n", q.frontQueue(&q));
    printf("Queue rear value: %d\n", q.rearQueue(&q));

    return 0;
}
