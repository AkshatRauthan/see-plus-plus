#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};

	// The array expression decays to a pointer
	// to its first element in this assignment.
	int *ptr = numbers;

	// Both point to the first element.
	printf("numbers: %p\n", (void *)numbers);
	printf("&numbers[0]: %p\n", (void *)&numbers[0]);
	printf("ptr: %p\n", (void *)ptr);

	// Accessing the first element through the pointer.
	printf("\nFirst element:\n");
	printf("numbers[0] = %d\n", numbers[0]);
	printf("*ptr       = %d\n", *ptr);

	// Pointer arithmetic after decay.
	printf("\nPointer arithmetic:\n");
	printf("*(ptr + 1) = %d\n", *(ptr + 1));
	printf("*(ptr + 2) = %d\n", *(ptr + 2));
	printf("*(ptr + 3) = %d\n", *(ptr + 3));

	// Array indexing can be performed through the pointer.
	printf("\nIndexing through pointer:\n");

	for (int i = 0; i < 5; i++) {
		printf("ptr[%d] = %d\n", i, ptr[i]);
	}

	return 0;
}
