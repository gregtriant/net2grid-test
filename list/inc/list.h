#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

/**
 * @brief Linked List Node structure.
 * data is a pointer to the data stored in the node.
 * next is a pointer to the next node in the list.
 */
typedef struct ListNode
{
    void *data;
    struct ListNode *next;
} ListNode;

/**
 * @brief Function pointer type for custom memory allocation.
 * @param size Size of memory to allocate.
 * @return Pointer to the allocated memory.
 */
typedef void *(*MyAlloc)(size_t size);

/**
 * @brief Function pointer type for custom memory deallocation.
 * @param data Pointer to the data to be freed.
 */
typedef void (*MyFree)(void *data);

/**
 * @brief Function pointer type for printing the data in the list node.
 * @param data Pointer to the data to be printed.
 */
typedef void (*ListNodePrinter)(void *data);

/**
 * Function to create a new list node.
 * @param data Pointer to the data to be stored in the node.
 * @param dataSize Size of the data to be copied.
 * @param allocFunc Function pointer for custom memory allocation.
 * @param freeFunc Function pointer for custom memory deallocation.
 * @return Pointer to the newly created ListNode, or NULL on failure.
 */
ListNode *createNode(void *data, size_t dataSize, MyAlloc allocFunc, MyFree freeFunc)
{
    ListNode *newNode = (ListNode *)allocFunc(sizeof(ListNode));
    if (!newNode)
    {
        return NULL; // Memory allocation failed
    }
    newNode->data = allocFunc(dataSize);
    if (!newNode->data)
    {
        freeFunc(newNode); // Free the node if data allocation fails
        return NULL;
    }
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    return newNode;
}

/**
 * Function to insert a new node at the beginning of the list.
 * @param head Pointer to the head of the list.
 * @param data Pointer to the data to be stored in the node.
 * @param dataSize Size of the data to be copied.
 * @param allocFunc Function pointer for custom memory allocation.
 * @param freeFunc Function pointer for custom memory deallocation.
 */
void insertBeginning(ListNode **head, void *data, size_t dataSize, MyAlloc allocFunc, MyFree freeFunc)
{
    ListNode *newNode = createNode(data, dataSize, allocFunc, freeFunc);
    if (newNode)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        DEBUG_PRINT("Failed to insert node at beginning\n");
        return;
    }
}

/**
 * Function to insert a new node at the end of the list.
 * @param head Pointer to the head of the list.
 * @param data Pointer to the data to be stored in the node.
 * @param dataSize Size of the data to be copied.
 * @param allocFunc Function pointer for custom memory allocation.
 * @param freeFunc Function pointer for custom memory deallocation.
 */
void insertEnd(ListNode **head, void *data, size_t dataSize, MyAlloc allocFunc, MyFree freeFunc)
{
    ListNode *newNode = createNode(data, dataSize, allocFunc, freeFunc);
    if (!newNode)
    {
        DEBUG_PRINT("Failed to insert node at end\n");
        return;
    }

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        ListNode *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

/**
 * Function to insert a new node at a specific position in the list.
 * @param head Pointer to the head of the list.
 * @param data Pointer to the data to be stored in the node.
 * @param dataSize Size of the data to be copied.
 * @param position Position at which to insert the new node.
 * @param allocFunc Function pointer for custom memory allocation.
 * @param freeFunc Function pointer for custom memory deallocation.
 */
void insertAt(ListNode **head, void *data, size_t dataSize, int position, MyAlloc allocFunc, MyFree freeFunc)
{
    if (head == NULL || data == NULL || dataSize <= 0 || position < 0)
    {
        DEBUG_PRINT("Invalid parameters\n");
        return;
    }

    // Check if the list is empty and position is 0
    if (position == 0)
    {
        insertBeginning(head, data, dataSize, allocFunc, freeFunc);
        return;
    }

    ListNode *newNode = createNode(data, dataSize, allocFunc, freeFunc);
    if (!newNode)
    {
        DEBUG_PRINT("Failed to insert node at position %d\n", position);
        return;
    }

    ListNode *current = *head;
    for (int i = 0; i < position - 1 && current != NULL; i++)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        DEBUG_PRINT("Position out of bounds\n");
        freeFunc(newNode->data);
        freeFunc(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

/**
 * Function to delete a node at a specific position in the list.
 * @param head Pointer to the head of the list.
 * @param position Position of the node to be deleted.
 * @param freeFunc Function pointer for custom memory deallocation.
 */
void deleteNodeAt(ListNode **head, int position, MyFree freeFunc)
{
    if (head == NULL || *head == NULL || position < 0)
    {
        DEBUG_PRINT("Head is NULL or position < 0\n");
        return;
    }

    ListNode *current = *head;
    ListNode *previous = NULL;
    for (int i = 0; i < position && current != NULL; i++)
    {
        previous = current;
        current = current->next;
    }
    if (previous != NULL)
    {
        previous->next = current->next;
        // delete current

        freeFunc(current->data);
        freeFunc(current);
    }
    else
    {
        // Deleting the head node
        *head = current->next;
        freeFunc(current->data);
        freeFunc(current);
    }
}

/**
 * Function to retrieve the value at a specific position in the list.
 * @param head Pointer to the head of the list.
 * @param position Position of the node to retrieve the value from.
 * @return Pointer to the data stored in the node, or NULL if not found.
 */
void *valueAt(ListNode **head, int position)
{
    if (head == NULL || position < 0)
    {
        DEBUG_PRINT("Invalid parameters\n");
        return NULL;
    }

    ListNode *current = *head;
    for (int i = 0; i < position && current != NULL; i++)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        DEBUG_PRINT("Position out of bounds\n");
        return NULL;
    }
    return current->data; // Return the data pointer directly
}

/**
 * Function to get the size of the list.
 * @param head Pointer to the head of the list.
 * @return Size of the list.
 */
int getSize(ListNode **head)
{
    int size = 0;
    ListNode *current = *head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

/**
 * Function to free the entire list.
 * @param head Pointer to the head of the list.
 * @param freeFunc Function pointer for custom memory deallocation.
 */
void freeList(ListNode **head, MyFree freeFunc)
{
    ListNode *current = *head;
    ListNode *nextNode;
    while (current != NULL)
    {
        nextNode = current->next;
        freeFunc(current->data);
        freeFunc(current);
        current = nextNode;
    }
    *head = NULL; // Set head to NULL after freeing the list
}

#ifdef DEBUG
void printList(ListNode *head, ListNodePrinter printFunc)
{
    ListNode *current = head;
    while (current != NULL)
    {
        printFunc(current->data);
        if (current->next != NULL)
        {
            DEBUG_PRINT(" -> ");
        }
        current = current->next;
    }
}
void printInt(void *data)
{
    DEBUG_PRINT("%d", *(int *)data);
}

void printString(void *data)
{
    DEBUG_PRINT("%s", (char *)data);
}

void printFloat(void *data)
{
    DEBUG_PRINT("%f", *(float *)data);
}

void printDouble(void *data)
{
    DEBUG_PRINT("%lf", *(double *)data);
}
#endif