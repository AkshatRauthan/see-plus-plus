#include <stdio.h>

int main(void) {
	// Three independent integer variables.
	int first = 100;
	int second = 200;
	int third = 300;

	// Multiple pointers can point to the same variable.
	int *ptr1 = &first;
	int *ptr2 = &first;
	int *ptr3 = &second;

	// Build an indirection chain.
	int **doublePtr = &ptr1;
	int ***triplePtr = &doublePtr;

	printf("=== Initial Values ===\n");
	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("third: %d\n\n", third);

	// All of these expressions reach first through different paths.
	printf("=== Multiple Pointers to the Same Variable ===\n");
	printf("*ptr1: %d\n", *ptr1);
	printf("*ptr2: %d\n", *ptr2);
	printf("**doublePtr: %d\n", **doublePtr);
	printf("***triplePtr: %d\n\n", ***triplePtr);

	// Reassign ptr1 indirectly through doublePtr.
	// ptr1 now points to third instead of first.
	*doublePtr = &third;

	printf("=== After Reassigning ptr1 ===\n");
	printf("*ptr1: %d\n", *ptr1);
	printf("*ptr2: %d\n", *ptr2);
	printf("*ptr3: %d\n", *ptr3);
	printf("**doublePtr: %d\n", **doublePtr);
	printf("***triplePtr: %d\n\n", ***triplePtr);

	// Modify third through the triple-pointer chain.
	***triplePtr = 999;

	printf("=== After Modifying Through Triple Pointer ===\n");
	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("third: %d\n", third);
	printf("*ptr1: %d\n", *ptr1);
	printf("*ptr2: %d\n", *ptr2);
	printf("*ptr3: %d\n", *ptr3);
	printf("***triplePtr: %d\n", ***triplePtr);

	return 0;
}
