#include <stdio.h>
#include <stdlib.h>

// Allocates an integer array and returns its address to the caller.
int *CreateArray(size_t length) {
    // Allocate memory for the requested number of integers.
    int *memory = malloc(length * sizeof *memory);

    // Return NULL if allocation fails.
    if (memory == NULL) {
        return NULL;
    }

    // Initialize the allocated elements.
    for (size_t i = 0; i < length; i++) {
        memory[i] = (int)(i + 1) * 10;
    }

    // Return the address of the dynamically allocated array.
    return memory;
}

int main(void) {
    size_t length = 5;

    // Receive the dynamically allocated array directly.
    int *array = CreateArray(length);

    // Check whether allocation succeeded.
    if (array == NULL) {
        fprintf(stderr, "Array allocation failed.\n");
        return 1;
    }

    // Display the returned array.
    printf("Dynamically Allocated Array:\n");

    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Modify an element through the returned pointer.
    array[2] = 999;

    printf("\nAfter Modification:\n");

    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // The caller is responsible for releasing the allocation.
    free(array);
    array = NULL;

    return 0;
}
