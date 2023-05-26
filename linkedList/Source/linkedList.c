#include "linkedList.h"

Node *createNote(int value)
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
void pushBack(Node **head, int value)
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
 * @brief Get the Node object
 * 
 * @param head 
 * @param node_number 
 * @return int 
 */
int getNode(Node **head, int node_number)
{
	Node *ptr = *head;
	for (int i = 0; i < node_number; i++)
	{
		ptr = ptr->next;
		if (ptr == NULL)
		{
			return -1;
		}
	}
	return ptr->value;
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

// Hàm được sử dụng để loại bỏ tất cả các phần tử của vùng chứa vector.
void clear(Node **head)
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

// return size of the linked list
int size(Node *head)
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

// erase node at index in linked list
void erase(Node **head, int pos)
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

// assign a Node with a given value
void assign(Node **head, int index, int value)
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
