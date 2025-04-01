#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "defs.h"
#include "list.h"

/**
 * @brief The custom free function to be used with the linked list 
 */ 
void freeFunc(void *data) {
    free(data);
}

/**
 * @brief The custom allocation function to be used with the linked list
 */
void *allocFunc(size_t size) {
    return malloc(size);
}

/**
 * @brief Struct to represent a number stored in a linked list.
 * This struct contains a pointer to the head of the linked list and a boolean flag indicating whether the number is signed or not.
 */
typedef struct {
    ListNode* head;
    bool isSigned;
} Number;

/**
 * @brief Struct to represent a 3-byte storage.
 * This struct contains an array of 3 bytes to store the value.
 */
typedef struct
{
    uint8_t bytes[3];
} ThreeByteStorage;

/**
 * @brief a macro to define a storage type with a specified number of bytes.
 * This macro can be used to create a struct with a specified number of bytes.
 * /
/** #define DEFINE_STORAGE(name, numBytes) \
*     typedef struct                     \
*     {                                  \
*         uint8_t bytes[numBytes];       \
*     } name;

* DEFINE_STORAGE(ByteStorage, 3)
*/

/**
 * @brief Store a 3-byte value into a linked list.
 */
void store(Number *number, uint64_t value) {
    while (value > 0)
    {
        // Create a new 3-byte storage object
        ThreeByteStorage storage;
        storage.bytes[0] = (value & 0xFF);
        storage.bytes[1] = (value >> 8) & 0xFF;
        storage.bytes[2] = (value >> 16) & 0xFF;

        // Add the storage to the linked list
        insertEnd(&number->head, &storage, sizeof(ThreeByteStorage), allocFunc, freeFunc);

        // Update the value to remove the stored bytes
        value >>= 24;
    }
}

/**
 * @brief Retrieve a 3-byte value from a linked list.
 */
uint64_t retrieve(Number *number) {
    uint64_t value = 0;
    int shift = 0;

    // Iterate through the linked list
    ListNode *current = number->head;
    while (current != NULL)
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


/**
 * * @brief Store a value into a linked list of 3-byte storage.
 */
void storeToLinkedList(Number* number, uint64_t value)
{
    number->isSigned = false;
    store(number, value);
}

/**
 * @brief Store a signed value into a linked list of 3-byte storage.
 * This function uses two's complement to store signed values as unsigned.
 */
void storeToLinkedListSinged(Number* number, int64_t value)
{
    number->isSigned = true;
    uint64_t complement = ~value + 1;
    store(number, complement);
}

/**
 * @brief Retrieve a signed value from a linked list of 3-byte storage.
 */
uint64_t retrieveFromLinkedList(Number* number)
{
    uint64_t value = retrieve(number);
    return value;
}

/**
 * @brief Retrieve a signed value from a linked list of 3-byte storage.
 * This function uses two's complement to retrieve signed values from unsigned.
 */
int64_t retrieveFromLinkedListSigned(Number* number)
{
    uint64_t value = retrieve(number);
    int64_t complement = ~value + 1;
    return complement;
}
