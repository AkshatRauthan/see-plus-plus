#include <stdio.h>

// Receives a copy of an int pointer.
// Changing ptr inside this function does not change the caller's pointer.
void ReassignPointer(int *ptr, int *target) {
	// This only changes the local copy of ptr.
	ptr = target;

	printf("Inside ReassignPointer:\n");
	printf("ptr points to: %d\n", *ptr);
}

// Receives the address of the caller's pointer (int **).
// This allows the function to modify the caller's actual pointer.
void ReassignPointerThroughDoublePointer(int **ptr, int *target) {
	// Dereferencing ptr accesses the caller's pointer variable.
	// Assigning target changes where the caller's pointer points.
	*ptr = target;

	printf("Inside ReassignPointerThroughDoublePointer:\n");
	printf("*ptr points to: %d\n", **ptr);
}

int main(void) {
	int first = 100;
	int second = 200;

	// ptr initially points to first.
	int *ptr = &first;

	printf("Initial State:\n");
	printf("ptr points to: %d\n\n", *ptr);

	// Passing ptr by value copies its address into the function parameter.
	// Reassignment inside the function affects only that local copy.
	ReassignPointer(ptr, &second);

	printf("\nAfter ReassignPointer:\n");
	printf("ptr still points to: %d\n\n", *ptr);

	// Passing the address of ptr allows the function to modify ptr itself.
	ReassignPointerThroughDoublePointer(&ptr, &second);

	printf("\nAfter ReassignPointerThroughDoublePointer:\n");
	printf("ptr now points to: %d\n", *ptr);

	return 0;
}
