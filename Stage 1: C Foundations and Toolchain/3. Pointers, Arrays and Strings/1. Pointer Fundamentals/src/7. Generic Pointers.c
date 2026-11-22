#include <stdio.h>

int main(void) {
	// Declare objects of different types.
	int number = 42;
	char character = 'A';
	float decimal = 3.14f;
	double precise_decimal = 9.81;

	// Declare a generic pointer.
	void *pointer = NULL;

	// Point to an integer.
	pointer = &number;

	printf("Integer:\n");
	printf("Address: %p\n", pointer);
	printf("Value: %d\n", *(int *)pointer);

	// Point to a character.
	pointer = &character;

	printf("\nCharacter:\n");
	printf("Address: %p\n", pointer);
	printf("Value: %c\n", *(char *)pointer);

	// Point to a float.
	pointer = &decimal;

	printf("\nFloat:\n");
	printf("Address: %p\n", pointer);
	printf("Value: %.2f\n", *(float *)pointer);

	// Point to a double.
	pointer = &precise_decimal;

	printf("\nDouble:\n");
	printf("Address: %p\n", pointer);
	printf("Value: %.2f\n", *(double *)pointer);

	return 0;
}
