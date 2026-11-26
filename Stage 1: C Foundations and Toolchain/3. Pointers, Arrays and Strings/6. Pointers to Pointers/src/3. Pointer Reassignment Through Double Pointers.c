#include <stdio.h>

int main(void) {
	int first = 100;
	int second = 200;

	// ptr initially points to first.
	int *ptr = &first;

	// doublePtr points to ptr, allowing us to modify ptr indirectly.
	int **doublePtr = &ptr;

	printf("Before Reassignment:\n");
	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("*ptr: %d\n", *ptr);
	printf("**doublePtr: %d\n\n", **doublePtr);

	// Reassign ptr through doublePtr.
	// *doublePtr refers to ptr itself, so ptr now points to second.
	*doublePtr = &second;

	printf("After Reassignment:\n");
	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("*ptr: %d\n", *ptr);
	printf("**doublePtr: %d\n\n", **doublePtr);

	// Modify the value currently reached through the pointer chain.
	// Since ptr now points to second, this changes second.
	**doublePtr = 500;

	printf("After Modifying the New Target:\n");
	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("*ptr: %d\n", *ptr);
	printf("**doublePtr: %d\n", **doublePtr);

	return 0;
}
