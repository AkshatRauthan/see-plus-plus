#include <stdio.h>

int main(void) {
	// Three independent integer variables.
	int first = 10;
	int second = 20;
	int third = 30;

	// An array containing pointers to integers.
	// Each element stores the address of a different integer.
	int *ptrArray[3] = {&first, &second, &third};

	// ptr points to the first element of ptrArray.
	// Its type is int ** because ptrArray elements are int *.
	int **ptr = ptrArray;

	printf("=== Array of Pointers ===\n");

	// Access each integer through the array of pointers.
	for (size_t i = 0; i < 3; i++) {
		printf("ptrArray[%zu] -> %d\n", i, *ptrArray[i]);
	}

	printf("\n=== Access Through Double Pointer ===\n");

	// ptr points to ptrArray[0].
	// Dereferencing ptr retrieves the first int pointer.
	// Dereferencing again retrieves the integer value.
	printf("*ptr: %d\n", **ptr);

	// Pointer arithmetic moves across elements of ptrArray.
	// Each increment moves by sizeof(int *).
	printf("Second element: %d\n", **(ptr + 1));
	printf("Third element: %d\n", **(ptr + 2));

	printf("\n=== Modifying Values Through Double Pointer ===\n");

	// ptr + 1 points to ptrArray[1].
	// *(ptr + 1) accesses ptrArray[1].
	// **(ptr + 1) accesses the integer second.
	**(ptr + 1) = 200;

	printf("first: %d\n", first);
	printf("second: %d\n", second);
	printf("third: %d\n", third);

	printf("\n=== Reassigning an Array Pointer Element ===\n");

	// Change ptrArray[0] to point to third instead of first.
	// ptr allows us to modify the pointer stored in the array.
	*ptr = &third;

	printf("ptrArray[0] now points to: %d\n", **ptr);
	printf("first remains: %d\n", first);
	printf("third remains: %d\n", third);

	return 0;
}
