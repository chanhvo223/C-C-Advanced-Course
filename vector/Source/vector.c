#include "vector.h"

/**
 * @brief Create a Note object
 * 
 * @param value 
 * @return Node* 
 */
static Node *createNote(int value)
{
	Node *temp;
	temp = (Node *)malloc(sizeof(Node));
	temp->value = value;
	temp->next = NULL;
	return temp;
}

/**
 * @brief push a new value to the last element of the linked
 *
 * @param head linked list head
 * @param value
 */
static void pushBack(Node **head, int value)
{
	Node *newNode, *lastNode;
	newNode = createNote(value);
	// if is_node_1
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

	lastNode = *head;
	// find lastNode->next == NULL
	while (lastNode->next != NULL)
	{
		lastNode = lastNode->next;
	}
	lastNode->next = newNode;
}

/**
 * @brief Get the Node's value at the given index
 *
 * @param head
 * @param index
 * @return int
 */
static void getNode(Node **head, int index)
{
	Node *ptr = *head;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
		if (ptr == NULL)
		{
			exit(1);
		}
	}
	printf("%d\n", ptr->value);
}

void addAtHead(Node **head, int value)
{
	Node *temp;
	temp = createNote(value);
	// check 1st condition
	if (*head == NULL)
	{
		*head = temp;
	}
	else
	{
		temp->next = *head;
		*head = temp;
	}
}

/**
 * @brief Clear all nodes
 * 
 * @param head 
 */
static void clear(Node **head)
{
	Node *temp;
	while ((*head) != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*head = NULL;
}

/**
 * @brief Set node's size
 * 
 * @param head 
 * @return int 
 */
static int size(Node *head)
{
	int size = 0;
	// from head to lastNode
	while (head->next != NULL)
	{
		head = head->next;
		size++;
	}

	return size + 1;
}

/**
 * @brief erase a node at given position
 * 
 * @param head 
 * @param pos 
 */
static void erase(Node **head, int pos)
{
	// check if that pos exists
	if (size((*head)) < pos)
	{
		printf("pos is out of range\n");
		return;
	}

	// find preNode and currNode
	Node *preNode, *currNode;
	currNode = *head;

	while (pos > 0)
	{
		preNode = currNode;
		currNode = currNode->next;
		pos--;
	}

	preNode->next = currNode->next;

	// Free currNode and linked preNode and afterNode
	free(currNode);
}

/**
 * @brief Assign a node'index to new value
 * 
 * @param head 
 * @param index 
 * @param value 
 */
static void assign(Node **head, int index, int value)
{
	// check if that pos exists
	if (size((*head)) < index)
	{
		printf("pos is out of range\n");
		return;
	}

	// find preNode, afterNode and currNode
	Node *currNode;
	currNode = *head;

	while (index > 0)
	{
		currNode = currNode->next;
		index--;
	}

	currNode->value = value;
}

void vectorInit(Vector *vector)
{
	vector->node = createNote(0);
	vector->pushBack = &pushBack;
	vector->getNode = &getNode;
	vector->size = &size;
	vector->clear = &clear;
	vector->erase = &erase;
	vector->assign = &assign;
}