#include <stdio.h>
#include <stdlib.h>

// Allocates a dynamic integer array and stores its address
// in the caller's pointer through a double pointer.
int AllocateArray(int **array, size_t length) {
    // Allocate memory for length integers.
    int *memory = malloc(length * (sizeof *memory));

    // Return failure if memory allocation was unsuccessful.
    if (memory == NULL) {
        return 0;
    }

    // Initialize every element of the allocated array.
    for (size_t i = 0; i < length; i++) {
        memory[i] = (int)(i + 1) * 10;
    }

    // Update the caller's pointer to reference the allocation.
    *array = memory;

    return 1;
}

int main(void) {
    size_t length = 5;

    // Initially, the pointer doesn't refer to any array.
    int *array = NULL;

    printf("Before Allocation:\n");
    printf("array: %p\n\n", (void *)array);

    // Pass the address of array so the function can update it.
    if (!AllocateArray(&array, length)) {
        fprintf(stderr, "Failed to allocate array.\n");
        return 1;
    }

    printf("After Allocation:\n");
    printf("array: %p\n", (void *)array);

    // Access dynamically allocated elements like a normal array.
    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Modify an element through the allocated array.
    array[2] = 999;

    printf("\nAfter Modification:\n");
    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Release the dynamically allocated array.
    free(array);

    // Reset the pointer to avoid retaining a dangling address.
    array = NULL;

    printf("\nAfter Deallocation:\n");
    printf("array: %p\n", (void *)array);

    return 0;
}
