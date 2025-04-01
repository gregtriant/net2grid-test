#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

typedef struct ListNode
{
    void *data;
    struct ListNode *next;
} ListNode;

typedef void (*ListNodeDestructor)(void *data);
typedef void (*ListNodePrinter)(void *data);

/**
 * Function to create a new list node.
 * @param data Pointer to the data to be stored in the node.
 * @param dataSize Size of the data to be copied.
 * @return Pointer to the newly created ListNode, or NULL on failure.
 */
ListNode *createNode(void *data, size_t dataSize)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (!newNode)
    {
        return NULL; // Memory allocation failed
    }
    newNode->data = malloc(dataSize);
    if (!newNode->data)
    {
        free(newNode); // Free the node if data allocation fails
        return NULL;
    }
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    return newNode;
}

void insertBeginning(ListNode **head, void *data, size_t dataSize)
{
    ListNode *newNode = createNode(data, dataSize);
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

void insertEnd(ListNode **head, void *data, size_t dataSize)
{
    ListNode *newNode = createNode(data, dataSize);
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

void insertAt(ListNode **head, void *data, size_t dataSize, int position) {
    if (head == NULL || data == NULL || dataSize <= 0 || position < 0)
    {
        DEBUG_PRINT("Invalid parameters\n");
        return;
    }

    // Check if the list is empty and position is 0
    if (position == 0)
    {
        insertBeginning(head, data, dataSize);
        return;
    }

    ListNode *newNode = createNode(data, dataSize);
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
        free(newNode->data);
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void deleteNodeAt(ListNode **head, int position, ListNodeDestructor destructor) {
    if (head == NULL || *head == NULL || position < 0) {
        DEBUG_PRINT("Head is NULL or position < 0\n");
        return;
    } 

    ListNode *current = *head;
    ListNode *previous = NULL;
    for (int i = 0; i < position && current != NULL; i++) {
        previous = current;
        current = current->next;
    }
    if (previous != NULL) {
        previous->next = current->next;
        // delete current
        if (destructor) {
            destructor(current->data);
        } else {
            free(current->data);
        }
        free(current);
    } else {
        // Deleting the head node
        *head = current->next;
        if (destructor) {
            destructor(current->data);
        } else {
            free(current->data);
        }
        free(current);
    }
}

void* valueAt(ListNode **head, int position, size_t dataSize) {
    if (head == NULL || position < 0) {
        DEBUG_PRINT("Invalid parameters\n");
        return NULL;
    }

    ListNode *current = *head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        DEBUG_PRINT("Position out of bounds\n");
        return NULL;
    }
    // Create a copy of the data to return
    void* dataCopy = malloc(dataSize);
    if (dataCopy == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    memcpy(dataCopy, current->data, dataSize);

    return dataCopy;
}

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

void printList(ListNode *head, ListNodePrinter printFunc)
{
    DEBUG_PRINT("List size: %d\n", getSize(&head));
    ListNode *current = head;
    while (current != NULL)
    {
        printFunc(current->data);
        if (current->next != NULL) {
            DEBUG_PRINT(" -> ");
        }
        current = current->next;
    }
}

void freeList(ListNode **head, ListNodeDestructor destructor) {
    ListNode *current = *head;
    ListNode *nextNode;
    while (current != NULL)
    {
        nextNode = current->next;
        if (destructor)
        {
            destructor(current->data);
        }
        free(current->data);
        free(current);
        current = nextNode;
    }
    *head = NULL; // Set head to NULL after freeing the list
}

void printInt(void *data) {
    DEBUG_PRINT("%d", *(int *)data);
}

void printString(void *data) {
    DEBUG_PRINT("%s", (char *)data);
}

// char* printInt(void *data) {
//     char *str = (char *)malloc(12); // Enough space for an int
//     if (str) {
//         snprintf(str, 12, "%d", *(int *)data);
//     }
//     return str; // Return the string for potential further use
// }

// char* printString(void *data) {
//     return (char *)data; // Return the string for potential further use
// }

void printFloat(void *data) {
    DEBUG_PRINT("%f", *(float *)data);
}

void printDouble(void *data) {
    DEBUG_PRINT("%lf", *(double *)data);
}

// void freeFunction(void *data) {
//     free(data); // Assuming data was dynamically allocated
// }