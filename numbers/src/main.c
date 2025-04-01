#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "byteInt.h"


int main()
{
    DEBUG_PRINT("\nRunning 3 byte int db with linked list!\n\n");

    Number number = {.head = NULL, .isSigned = false};
    uint32_t value = 0x123456;
    DEBUG_PRINT("Storing signed value: 0x%x\n", value);
    storeToLinkedList(&number, value);
    if (number.isSigned)
    {
        DEBUG_PRINT("value: %ld\n", retrieveFromLinkedListSigned(&number));
    }
    else
    {
        DEBUG_PRINT("value: 0x%lx\n", retrieveFromLinkedList(&number));
    }
    DEBUG_PRINT("list size: %d\n\n", getSize(&number.head));


    Number number2 = {.head = NULL, .isSigned = false};
    int64_t value2 = -0x1234567899912;
    DEBUG_PRINT("Storing signed value: %ld\n", value2);
    storeToLinkedListSinged(&number2, value2);
    if (number2.isSigned)
    {
        DEBUG_PRINT("value: %ld\n", retrieveFromLinkedListSigned(&number2));
    }
    else
    {
        DEBUG_PRINT("value: %ld\n", retrieveFromLinkedList(&number2));
    }
    DEBUG_PRINT("list size: %d\n", getSize(&number2.head));


    if (number.head != NULL)
        freeList(&number.head, freeFunc);
    if (number2.head != NULL)
        freeList(&number2.head, freeFunc);
    return 0;
}