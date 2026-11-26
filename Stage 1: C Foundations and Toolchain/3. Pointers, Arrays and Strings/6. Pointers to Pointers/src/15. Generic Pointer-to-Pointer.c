#include <stdio.h>
#include <stdlib.h>

// Allocates memory for an object of the requested size.
// The output parameter receives the resulting generic pointer.
int AllocateMemory(void **output, size_t size) {
	// Allocate the requested number of bytes.
	void *memory = malloc(size);

	// Return failure if allocation was unsuccessful.
	if (memory == NULL) {
		return 0;
	}

	// Update the caller's void pointer.
	*output = memory;

	return 1;
}

int main(void) {
	// Example 1: Allocate memory for an integer.
	int *integer = NULL;

	// Pass the address of an actual void * object.
	void *memory = NULL;
	if (!AllocateMemory(&memory, sizeof *integer)) {
		fprintf(stderr, "Integer allocation failed.\n");
		return 1;
	}
	
	// Convert the returned generic pointer to the required type.
	integer = memory;

	// Initialize the allocated integer.
	*integer = 100;

	printf("Integer Allocation:\n");
	printf("Value: %d\n", *integer);

	free(integer);
	integer = NULL;

	// Example 2: Allocate memory for a double.
	double *decimal = NULL;

	if (!AllocateMemory((void **)&decimal, sizeof *decimal)) {
		fprintf(stderr, "Double allocation failed.\n");
		return 1;
	}

	// Initialize the allocated double.
	*decimal = 45.75;

	printf("\nDouble Allocation:\n");
	printf("Value: %.2f\n", *decimal);

	free(decimal);
	decimal = NULL;

	// Example 3: Allocate memory for an array of integers.
	int *array = NULL;
	size_t length = 5;

	if (!AllocateMemory((void **)&array, length * sizeof *array)) {
		fprintf(stderr, "Array allocation failed.\n");
		return 1;
	}

	// Initialize the allocated integer array.
	for (size_t i = 0; i < length; i++) {
		array[i] = (int)(i + 1) * 10;
	}

	printf("\nInteger Array Allocation:\n");

	for (size_t i = 0; i < length; i++) {
		printf("array[%zu] = %d\n", i, array[i]);
	}

	free(array);
	array = NULL;

	return 0;
}
