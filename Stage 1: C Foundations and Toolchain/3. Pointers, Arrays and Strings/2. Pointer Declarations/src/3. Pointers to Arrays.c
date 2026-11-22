#include <stdio.h>

int main(void) {
    // Declare an array containing five integers.
    int numbers[5] = {10, 20, 30, 40, 50};

    // Pointer to the entire array of five integers.
    int (*array_pointer)[5] = &numbers;

    printf("Array Information:\n");

    printf("Array address: %p\n", (void *)&numbers);
    printf("Pointer value: %p\n", (void *)array_pointer);

    // Display the size of the pointer and pointed-to array.
    printf("\nSizes:\n");

    printf("sizeof(array_pointer): %zu bytes\n",
           sizeof(array_pointer));  // NOLINT(bugprone-sizeof-expression)

    printf("sizeof(*array_pointer): %zu bytes\n",
           sizeof(*array_pointer));

    // Access individual elements through the array pointer.
    printf("\nArray Elements:\n");

    for (size_t i = 0; i < 5; i++) {
        printf("Element %zu: %d\n", i, (*array_pointer)[i]);
    }

    // Modify an element through the pointer.
    (*array_pointer)[2] = 300;

    printf("\nAfter Modification:\n");

    for (size_t i = 0; i < 5; i++) {
        printf("Element %zu: %d\n", i, numbers[i]);
    }

    return 0;
}
