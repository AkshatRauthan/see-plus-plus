#include <stdio.h>

int main(void) {
	// Declare variables of different types.
	int number = 42;
	char character = 'A';
	float decimal = 3.14f;
	double precise_decimal = 9.81;

	// Create pointers with matching types.
	int *integer_pointer = &number;
	char *character_pointer = &character;
	float *float_pointer = &decimal;
	double *double_pointer = &precise_decimal;

	// Display the values of the original variables.
	printf("Original Values:\n");
	printf("Integer: %d\n", number);
	printf("Character: %c\n", character);
	printf("Float: %.2f\n", decimal);
	printf("Double: %.2f\n", precise_decimal);

	// Display the addresses stored in the pointers.
	printf("\nPointer Addresses:\n");
	printf("Integer pointer: %p\n", (void *)integer_pointer);
	printf("Character pointer: %p\n", (void *)character_pointer);
	printf("Float pointer: %p\n", (void *)float_pointer);
	printf("Double pointer: %p\n", (void *)double_pointer);

	// Access the original objects through their pointers.
	printf("\nValues Through Pointers:\n");
	printf("Integer: %d\n", *integer_pointer);
	printf("Character: %c\n", *character_pointer);
	printf("Float: %.2f\n", *float_pointer);
	printf("Double: %.2f\n", *double_pointer);

	return 0;
}
