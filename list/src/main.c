#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "list.h"


void freeString(void *data) {
    free(data); // Assuming data was dynamically allocated
}

int main()
{
    DEBUG_PRINT("\nRunning Linked List!\n");

    ListNode* head = NULL;
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;
    int data4 = 40;
    int data5 = 50;

    insertBeginning(&head, &data1, sizeof(int));
    insertEnd(&head, &data2, sizeof(int));
    insertEnd(&head, &data3, sizeof(int));
    insertBeginning(&head, &data4, sizeof(int));

    printList(head, printInt);
    DEBUG_PRINT("\n");

    insertAt(&head, &data5, sizeof(int), 4);
    printList(head, printInt);
    DEBUG_PRINT("\n");

    ListNode* head2 = NULL;
    for(int i=10; i<=50; i+=10) {
        insertEnd(&head2, &i, sizeof(int));
    }

    deleteNodeAt(&head2, 0, NULL);

    DEBUG_PRINT("\nList2\n");
    int size = getSize(&head2);
    for (int i=0; i<size; i++) {
        int* number = (int*)valueAt(&head2, i, sizeof(int));
        DEBUG_PRINT("%d: %d\n", i, *number);
    }

    int *number2 = (int*)valueAt(&head2, 20, sizeof(int));

    
    const int strSize = 5;
    ListNode* head3 = NULL;
    for(int i=10; i<=50; i+=10) {
        char* srt = (char*)malloc(strSize * sizeof(char));
        if (srt == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        sprintf(srt, "%d", i);
        insertEnd(&head3, srt, strSize);
        free(srt);
    }

    deleteNodeAt(&head3, 0, freeString);
    deleteNodeAt(&head3, 3, freeString);
    deleteNodeAt(&head3, 2, freeString);
    deleteNodeAt(&head3, 0, freeString);
    deleteNodeAt(&head3, 0, freeString);
    // deleteNodeAt(&head3, 0, freeString);
    // deleteNodeAt(&head3, -10, freeString);


    DEBUG_PRINT("\nList3\n");
    size = getSize(&head3);
    for (int i=0; i<size; i++) {
        char* str;
        str = (char*)valueAt(&head3, i, sizeof(strSize));
        DEBUG_PRINT("%d: %s\n", i, str);
    }

    freeList(&head, NULL);
    freeList(&head2, NULL);
    freeList(&head3, NULL);

    return 0;
}