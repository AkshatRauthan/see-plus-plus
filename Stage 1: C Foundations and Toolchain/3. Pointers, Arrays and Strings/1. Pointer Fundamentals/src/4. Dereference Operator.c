#include <stdio.h>

int main(void) {
	// Declare an integer variable.
	int number = 42;

	// Initialize a pointer with the address of number.
	int *pointer = &number;

	// Read the value directly.
	printf("Direct Access:\n");
	printf("number: %d\n", number);

	// Read the same value through the pointer.
	printf("\nPointer Access:\n");
	printf("*pointer: %d\n", *pointer);

	// Modify the original variable through the pointer.
	*pointer = 100;

	// Both accesses now return the updated value.
	printf("\nAfter Dereferencing Assignment:\n");
	printf("number: %d\n", number);
	printf("*pointer: %d\n", *pointer);

	// Modify the variable directly.
	number = 250;

	// The pointer observes the updated value.
	printf("\nAfter Direct Assignment:\n");
	printf("number: %d\n", number);
	printf("*pointer: %d\n", *pointer);

	return 0;
}
