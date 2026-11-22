#include <stdio.h>

/*
 * Function returning an integer.
 */
static int process(int value, char *text) {
	printf("Processing: %s\n", text);
	return value * 2;
}

/*
 * Function returning a character pointer.
 */
static char *get_text(void) {
	static char text[] = "Hello from a function pointer";
	return text;
}

int main(void) {
	int first = 10;
	int second = 20;

	/*
	 * Array of 2 pointers to integers.
	 *
	 * Each element stores the address of an integer.
	 */
	int *pointer_array[2] = {&first, &second};

	printf("Array of Pointers:\n");
	printf("First: %d\n", *pointer_array[0]);
	printf("Second: %d\n", *pointer_array[1]);

	/*
	 * Pointer to an array of 10 integers.
	 *
	 * The pointer stores the address of the entire array.
	 */
	int numbers[10] = {0};

	int(*array_pointer)[10] = &numbers;

	(*array_pointer)[0] = 100;
	(*array_pointer)[1] = 200;

	printf("\nPointer to Array:\n");
	printf("First: %d\n", (*array_pointer)[0]);
	printf("Second: %d\n", (*array_pointer)[1]);

	/*
	 * Pointer to a function that:
	 * - Accepts an int and a char pointer.
	 * - Returns an int.
	 */
	int (*function_pointer)(int, char *) = process;

	printf("\nFunction Pointer:\n");

	int result = function_pointer(10, "Example");

	printf("Result: %d\n", result);

	/*
	 * Array of 5 pointers to functions that:
	 * - Accept no arguments.
	 * - Return a char pointer.
	 */
	char *(*function_array[5])(void) = {get_text};

	printf("\nArray of Function Pointers:\n");
	printf("%s\n", function_array[0]());

	return 0;
}
