#include "main.h"

int main(int argc, char const *argv[])
{
    Node *n1 = NULL;
    pushBack(&n1, 1);
    pushBack(&n1, 2);
    pushBack(&n1, 4);
    pushBack(&n1, 6);
    pushBack(&n1, 123);

    for (int i = 0; i < size(n1); i++)
    {
        printf("%d\n", getNode(&n1, i));
    }

    return 0;
}