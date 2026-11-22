#include <stdio.h>

int main(void) {
	// Declare two variables.
	int number = 42;
	char character = 'A';

	// Display the variable values.
	printf("Variable Values:\n");
	printf("number: %d\n", number);
	printf("character: %c\n", character);

	// Display the memory addresses of the variables.
	printf("\nMemory Addresses:\n");
	printf("Address of number: %p\n", (void *)&number);
	printf("Address of character: %p\n", (void *)&character);

	// Display the amount of storage occupied by each object.
	printf("\nObject Sizes:\n");
	printf("Size of number: %zu bytes\n", sizeof(number));
	printf("Size of character: %zu bytes\n", sizeof(character));

	return 0;
}
