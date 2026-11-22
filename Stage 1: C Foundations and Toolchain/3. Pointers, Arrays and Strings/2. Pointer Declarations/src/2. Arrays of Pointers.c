#include <stdio.h>

int main(void) {
    // Declare three independent integer objects.
    int first = 10;
    int second = 20;
    int third = 30;

    // Create an array containing three integer pointers.
    int *pointers[3] = {
        &first,
        &second,
        &third
    };

    // Display the values of the original variables.
    printf("Original Variables:\n");
    printf("first: %d\n", first);
    printf("second: %d\n", second);
    printf("third: %d\n", third);

    // Display the addresses stored in the pointer array.
    printf("\nPointer Array:\n");

    for (size_t i = 0; i < 3; i++) {
        printf(
            "pointers[%zu]: %p\n",
            i,
            (void *)pointers[i]
        );
    }

    // Access the original objects through their pointers.
    printf("\nValues Through Pointers:\n");

    for (size_t i = 0; i < 3; i++) {
        printf(
            "*pointers[%zu]: %d\n",
            i,
            *pointers[i]
        );
    }

    // Modify the original variables through the pointers.
    *pointers[0] = 100;
    *pointers[1] = 200;
    *pointers[2] = 300;

    printf("\nAfter Modifying Through Pointers:\n");
    printf("first: %d\n", first);
    printf("second: %d\n", second);
    printf("third: %d\n", third);

    // Reassign the first pointer to another object.
    pointers[0] = &third;

    printf("\nAfter Reassigning pointers[0]:\n");
    printf("*pointers[0]: %d\n", *pointers[0]);

    // Modify third through the reassigned pointer.
    *pointers[0] = 500;

    printf("third: %d\n", third);

    return 0;
}
