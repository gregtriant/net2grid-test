#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "byteInt.h"

int main()
{
    DEBUG_PRINT("\nRunning 3 byte int db with linked list!\n");

    // Initialize the linked list
    ListNode *head = NULL;

    // Example: Storing and retrieving a small value
    uint32_t smallValue = 0x123456; // Example value within 3-byte range
    storeToLinkedList(&head, smallValue);
    printf("Retrieved small value: 0x%lX\n", retrieveFromLinkedList(head));
    
    // Reinitialize the list for a larger value
    ListNode *head2 = NULL;
    
    // Example: Storing and retrieving a large value
    uint64_t largeValue = 0x123456789ABCDEF; // Example value exceeding 3-byte range
    storeToLinkedList(&head2, largeValue);
    printf("Retrieved large value: 0x%lX\n", retrieveFromLinkedList(head2));
    
    freeList(&head, NULL);
    freeList(&head2, NULL);
    return 0;
}