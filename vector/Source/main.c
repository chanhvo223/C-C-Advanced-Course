#include "main.h"

int main()
{
    Vector array;
    vectorInit(&array);
    array.pushBack(&array.node, 21);
    array.pushBack(&array.node, 23);
    array.pushBack(&array.node, 31);
    array.erase(&array.node, 1);
    array.pushBack(&array.node, 123);
    array.pushBack(&array.node, 331);
    array.pushBack(&array.node, 3111);
    array.assign(&array.node, 4, 10);
    array.clear(&array.node);

    for (int i = 1; i < array.size(array.node); i++)
    {
        array.getNode(&array.node, i);
    }

    return 0;
}