#include <stdio.h>

/*
 * Prints an integer through a pointer.
 *
 * A null pointer is rejected before dereferencing.
 *
 * Returns:
 *    0 on success.
 *   -1 if the pointer is NULL.
 */
static int print_integer(const int *pointer) {
	if (pointer == NULL) {
		printf("No integer available.\n");
		return -1;
	}

	printf("Integer value: %d\n", *pointer);

	return 0;
}

int main(void) {
	// Initialize a pointer with NULL.
	int *pointer = NULL;

	printf("Initial Pointer State:\n");

	if (pointer == NULL) {
		printf("Pointer is NULL.\n");
	}

	// Passing a NULL pointer is safe because the function checks it.
	print_integer(pointer);

	// Declare an integer object.
	int number = 42;

	// Assign the address of the integer to the pointer.
	pointer = &number;

	printf("\nAfter Assigning an Address:\n");

	if (pointer != NULL) {
		printf("Pointer is valid.\n");
		print_integer(pointer);
	}

	// Reset the pointer to NULL.
	pointer = NULL;

	printf("\nAfter Resetting Pointer:\n");

	if (pointer == NULL) {
		printf("Pointer is NULL again.\n");
	}

	return 0;
}
