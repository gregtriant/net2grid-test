#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "list.h"

void freeFunc(void *data)
{
    free(data); // Assuming data was dynamically allocated
}

void *allocFunc(size_t size)
{
    return malloc(size); // Replace with your custom allocation function if needed
}

int main()
{
    #ifdef DEBUG

    DEBUG_PRINT("\nRunning Linked List!\n");
    
    ListNode *head2 = NULL;
    for (int i = 10; i <= 50; i += 10)
    {
        insertEnd(&head2, &i, sizeof(int), allocFunc, freeFunc);
    }
    
    deleteNodeAt(&head2, 0, freeFunc);
    
    DEBUG_PRINT("\nList of ints\n");
    int size = getSize(&head2);
    for (int i = 0; i < size; i++)
    {
        int *number = (int *)valueAt(&head2, i);
        DEBUG_PRINT("%d: %d\n", i, *number);
    }
    
    const int strSize = 5;
    ListNode *head3 = NULL;
    for (int i = 10; i <= 50; i += 10)
    {
        char *srt = (char *)malloc(strSize * sizeof(char));
        if (srt == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        sprintf(srt, "%d", i);
        insertEnd(&head3, srt, strSize, allocFunc, freeFunc);
        free(srt);
    }
    
    deleteNodeAt(&head3, 0, freeFunc);
    deleteNodeAt(&head3, 3, freeFunc);
    deleteNodeAt(&head3, 2, freeFunc);
    
    DEBUG_PRINT("\nList of strings\n");
    size = getSize(&head3);
    for (int i = 0; i < size; i++)
    {
        char *str;
        str = (char *)valueAt(&head3, i);
        if (str == NULL) {
            exit(EXIT_FAILURE);
        }
        DEBUG_PRINT("%d: %s\n", i, str);
    }
    
    freeList(&head2, freeFunc);
    freeList(&head3, freeFunc);

    #endif
    
    return 0;
}