#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

typedef struct CenterPoint
{
    Node *mid;
    struct CenterPoint *left, *right;
} CenterPoint;

/**
 * @brief Add new elements to  the linked list in order.
 *
 * @param head of the linked list
 * @param value which we are adding
 */
void addSortedNode(Node **head, int value)
{
    Node *newNode = createNode(value);

    // check if new node
    if (*head == NULL)
    {
        (*head) = newNode;
        return;
    }

    Node *temp, *preTemp;

    // if newNode.value < head.value => switch headNode to newNode
    if (newNode->data < (*head)->data)
    {
        temp = *head;

        *head = newNode;

        (*head)->next = temp;
    }
    // if greater than head.value then find the node.value > newNode.value
    else
    {
        temp = *head;

        // Find node.value > newNode.value
        while (newNode->data > temp->data)
        {
            preTemp = temp;
            temp = temp->next;

            // if temp is lastNode
            if (temp == NULL)
            {
                preTemp->next = newNode;
                return;
            }
        }

        // Add newNode between 2 nodes
        preTemp->next = newNode;
        newNode->next = temp;
    }
}

int getNode(Node *head, int node_number)
{
    Node *ptr = head;
    for (int i = 0; i < node_number; i++)
    {
        ptr = ptr->next;
        if (ptr == NULL)
        {
            return -1;
        }
    }
    return ptr->data;
}

int size(Node *head)
{
    int count = 0;
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

CenterPoint *createCenterPoint()
{
    CenterPoint *temp = (CenterPoint *)malloc(sizeof(CenterPoint));
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

/**
 * @brief Return All center points of the given linked list
 * 
 * @param head of the linked list
 * @param size of the linked list
 * @return CenterPoint* tree structure
 */
CenterPoint *findCenterPoint(Node **head, int size)
{
    if (size > 0)
    {
        CenterPoint *temp = createCenterPoint();
        temp->mid = *head;

        for (size_t i = (size / 2); i > 0; i--)
        {
            temp->mid = temp->mid->next;
        }

        // Center point left
        temp->left = findCenterPoint(head, (size / 2));
        // Center point right
        temp->right = findCenterPoint(&(temp->mid->next), (size - 1) / 2);

        return temp;
    }
    return NULL;
}

/**
 * @brief Binary search in the sorted linked list
 *
 * @param head of the linked list
 * @param value which we looking for
 * @param size of the linked list
 * @return value founded ? value : -1;
 */
int binarySearch(Node *head, int value, int size)
{
    if (size > 0)
    {
        // stop condition
        Node *mid = head;
        int count = size / 2;

        while (count >= 0)
        {
            mid = mid->next;
            count--;
        }

        if (mid->data == value)
        {
            return value;
        }

        if (mid->data > value)
        {
            return binarySearch(head, value, size / 2);
        }
        else
        {
            return binarySearch(mid->next, value, (size - 1) / 2);
        }
    }

    return -1;
}

int main()
{
    Node *n = NULL;
    addSortedNode(&n, 7);
    addSortedNode(&n, 4);
    addSortedNode(&n, 11);
    addSortedNode(&n, 12);
    addSortedNode(&n, 151);
    addSortedNode(&n, 256);
    addSortedNode(&n, 1);
    addSortedNode(&n, 5);
    addSortedNode(&n, 3);
    addSortedNode(&n, 1111);
    addSortedNode(&n, 154);
    addSortedNode(&n, 14);

    for (size_t i = 0; i <= size(n); i++)
    {
        printf("%d\n", getNode(n, i));
    }
    CenterPoint *cPoints;
    cPoints = findCenterPoint(&n, size(n));

    printf("binarySearch: %d\n", binarySearch(n, 25, size(n)));
    printf("binarySearch: %d\n", binarySearch(n, 11, size(n)));

    return 0;
}