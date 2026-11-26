#include <stdio.h>

int main(void) {
	int value = 100;

	// ptr stores the address of value.
	int *ptr = &value;

	// doublePtr stores the address of ptr.
	int **doublePtr = &ptr;

	printf("Before Modification:\n");
	printf("value: %d\n", value);
	printf("*ptr: %d\n", *ptr);
	printf("**doublePtr: %d\n\n", **doublePtr);

	// Dereferencing twice reaches the original integer.
	// Assigning through **doublePtr modifies value itself.
	**doublePtr = 500;

	printf("After Modification Through Double Pointer:\n");
	printf("value: %d\n", value);
	printf("*ptr: %d\n", *ptr);
	printf("**doublePtr: %d\n", **doublePtr);

	return 0;
}
