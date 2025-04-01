#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "list.h"

// Struct for 3-byte storage
typedef struct
{
    uint8_t bytes[3];
} ThreeByteStorage;

// Function to store a value into a linked list of 3-byte storage
void storeToLinkedList(ListNode **head, uint64_t value)
{
    while (value > 0)
    {
        // Create a new 3-byte storage object
        ThreeByteStorage storage;
        storage.bytes[0] = (value & 0xFF);
        storage.bytes[1] = (value >> 8) & 0xFF;
        storage.bytes[2] = (value >> 16) & 0xFF;

        // Add the storage to the linked list
        insertEnd(head, &storage, sizeof(ThreeByteStorage));

        // Update the value to remove the stored bytes
        value >>= 24;
    }
}

// Function to retrieve a value from a linked list of 3-byte storage
uint64_t retrieveFromLinkedList(ListNode *head)
{
    uint64_t value = 0;
    int shift = 0;

    // Iterate through the linked list
    ListNode *current = head;
    while (current)
    {
        ThreeByteStorage *storage = (ThreeByteStorage *)current->data;

        // Combine the bytes from the current storage into the value
        value |= ((uint64_t)storage->bytes[0] << shift);
        value |= ((uint64_t)storage->bytes[1] << (shift + 8));
        value |= ((uint64_t)storage->bytes[2] << (shift + 16));

        // Move to the next node and update the shift
        current = current->next;
        shift += 24;
    }

    return value;
}

// Function to free the linked list of 3-byte storage
void freeLinkedList(ListNode **head)
{
    freeList(head, free);
}