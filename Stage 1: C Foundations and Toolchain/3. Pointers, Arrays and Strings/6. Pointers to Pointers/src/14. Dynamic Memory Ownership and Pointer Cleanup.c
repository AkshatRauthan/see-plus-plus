#include <stdio.h>
#include <stdlib.h>

// Represents a dynamically allocated collection of integers.
struct IntegerArray {
    int *data;
    size_t length;
};

// Allocates an array and transfers ownership through the output pointer.
int CreateArray(struct IntegerArray **array, size_t length) {
    // Allocate the structure itself.
    struct IntegerArray *memory = malloc(sizeof *memory);

    if (memory == NULL) {
        return 0;
    }

    // Allocate the array stored inside the structure.
    memory->data = calloc(length, sizeof *memory->data);

    if (memory->data == NULL) {
        // Release the structure if its internal allocation fails.
        free(memory);
        return 0;
    }

    memory->length = length;

    // Transfer the structure pointer to the caller.
    *array = memory;

    return 1;
}

// Releases the structure and its owned array.
void DestroyArray(struct IntegerArray **array) {
    // Nothing to release if the pointer or allocation is NULL.
    if (array == NULL || *array == NULL) {
        return;
    }

    // Release the memory owned by the structure.
    free((*array)->data);
    (*array)->data = NULL;

    // Release the structure itself.
    free(*array);

    // Clear the caller's pointer to prevent accidental reuse.
    *array = NULL;
}

int main(void) {
    struct IntegerArray *array = NULL;

    // Create the allocation and receive ownership.
    if (!CreateArray(&array, 5)) {
        fprintf(stderr, "Array creation failed.\n");
        return 1;
    }

    // Initialize the array elements.
    for (size_t i = 0; i < array->length; i++) {
        array->data[i] = (int)(i + 1) * 10;
    }

    printf("Owned Array:\n");

    for (size_t i = 0; i < array->length; i++) {
        printf("array->data[%zu] = %d\n", i, array->data[i]);
    }

    // Demonstrate borrowing: another pointer temporarily accesses
    // the same allocation without taking ownership.
    int *borrowed = array->data;

    printf("\nBorrowed Pointer:\n");
    printf("borrowed[2] = %d\n", borrowed[2]);

    // Modify the shared allocation through the borrowed pointer.
    borrowed[2] = 999;

    printf("\nAfter Borrowed Pointer Modification:\n");
    printf("array->data[2] = %d\n", array->data[2]);

    // The borrowed pointer must not be used after the owner releases
    // the allocation.
    borrowed = NULL;

    // Destroy the owned allocation.
    DestroyArray(&array);

    printf("\nAfter Cleanup:\n");
    printf("array: %p\n", (void *)array);

    // Safe to call again because the pointer is now NULL.
    DestroyArray(&array);

    return 0;
}
