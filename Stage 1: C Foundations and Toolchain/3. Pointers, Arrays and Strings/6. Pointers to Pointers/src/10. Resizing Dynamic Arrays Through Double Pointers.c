#include <stdio.h>
#include <stdlib.h>

// Resizes a dynamically allocated integer array.
// A double pointer allows the function to update the caller's pointer.
int ResizeArray(int **array, size_t newLength) {
    // Store the result separately so the original allocation isn't lost
    // if realloc() fails.
    int *resized = realloc(*array, newLength * sizeof **array);

    // Return failure if resizing was unsuccessful.
    if (resized == NULL) {
        return 0;
    }

    // Update the caller's pointer with the resulting address.
    *array = resized;

    return 1;
}

int main(void) {
    size_t length = 3;

    // Allocate an initial array of three integers.
    int *array = malloc(length * sizeof *array);

    if (array == NULL) {
        fprintf(stderr, "Initial allocation failed.\n");
        return 1;
    }

    // Initialize the original elements.
    for (size_t i = 0; i < length; i++) {
        array[i] = (int)(i + 1) * 10;
    }

    printf("Original Array:\n");

    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Save the original pointer value for demonstration.
    printf("\nOriginal Address: %p\n", (void *)array);

    // Increase the array size from three elements to six.
    size_t newLength = 6;

    if (!ResizeArray(&array, newLength)) {
        fprintf(stderr, "Array resizing failed.\n");
        free(array);
        return 1;
    }

    // Update the tracked array length after successful resizing.
    length = newLength;

    printf("\nAfter Resizing:\n");
    printf("New Address: %p\n", (void *)array);

    // Initialize the newly added elements.
    for (size_t i = 3; i < length; i++) {
        array[i] = (int)(i + 1) * 10;
    }

    // Display all elements, including the newly added ones.
    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Shrink the array from six elements to two.
    newLength = 2;

    if (!ResizeArray(&array, newLength)) {
        fprintf(stderr, "Array shrinking failed.\n");
        free(array);
        return 1;
    }

    length = newLength;

    printf("\nAfter Shrinking:\n");

    for (size_t i = 0; i < length; i++) {
        printf("array[%zu] = %d\n", i, array[i]);
    }

    // Release the final allocation.
    free(array);
    array = NULL;

    return 0;
}
