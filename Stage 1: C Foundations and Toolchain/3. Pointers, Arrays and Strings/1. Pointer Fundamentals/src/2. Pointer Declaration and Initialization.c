#include <stdio.h>

int main(void) {
    // Declare two integer variables.
    int first = 10;
    int second = 20;

    // Declare and initialize a pointer to first.
    int *pointer = &first;

    // Inspect the initial pointer.
    printf("Initial Pointer:\n");
    printf("First value: %d\n", first);
    printf("Pointer address: %p\n", (void *)pointer);
    printf("Value through pointer: %d\n", *pointer);

    // Reassign the pointer to second.
    pointer = &second;

    // Inspect the reassigned pointer.
    printf("\nAfter Pointer Reassignment:\n");
    printf("Second value: %d\n", second);
    printf("Pointer address: %p\n", (void *)pointer);
    printf("Value through pointer: %d\n", *pointer);

    return 0;
}
