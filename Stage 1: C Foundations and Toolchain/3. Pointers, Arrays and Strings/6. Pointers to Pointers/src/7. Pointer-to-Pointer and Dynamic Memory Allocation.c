#include <stdio.h>
#include <stdlib.h>

// Allocate an integer dynamically and store its address in the caller's
// pointer. Using int ** allows us to modify the original pointer from main().
int AllocateInteger(int **ptr, int initialValue) {
	// Allocate memory for one integer on the heap.
	int *memory = malloc(sizeof *memory);

	// Check whether allocation succeeded.
	if (memory == NULL) {
		return 0;
	}

	// Initialize the allocated integer.
	*memory = initialValue;

	// Store the allocated address in the caller's pointer.
	*ptr = memory;

	return 1;
}

int main(void) {
	// Initially, ptr does not point to allocated memory.
	int *ptr = NULL;

	printf("Before Allocation:\n");
	printf("ptr: %p\n\n", (void *)ptr);

	// Pass the address of ptr so the function can update it.
	if (!AllocateInteger(&ptr, 100)) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}

	printf("After Allocation:\n");
	printf("ptr: %p\n", (void *)ptr);
	printf("*ptr: %d\n\n", *ptr);

	// Modify the dynamically allocated integer.
	*ptr = 500;

	printf("After Modification:\n");
	printf("*ptr: %d\n\n", *ptr);

	// Release the dynamically allocated memory.
	free(ptr);

	// Set the pointer to NULL after releasing the allocation.
	// This avoids retaining a dangling pointer in this variable.
	ptr = NULL;

	printf("After Deallocation:\n");
	printf("ptr: %p\n", (void *)ptr);

	return 0;
}
