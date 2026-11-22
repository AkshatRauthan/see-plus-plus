#include <stdio.h>

int main(void) {
	// Declare variables of different types.
	int number = 42;
	char character = 'A';
	float decimal = 3.14f;
	double precise_decimal = 9.81;

	// Retrieve and display their memory addresses.
	printf("Variable Addresses:\n");

	printf("number:           %p\n", (void *)&number);
	printf("character:        %p\n", (void *)&character);
	printf("decimal:          %p\n", (void *)&decimal);
	printf("precise_decimal:  %p\n", (void *)&precise_decimal);

	// Store the addresses in compatible pointers.
	int *number_address = &number;
	char *character_address = &character;
	float *decimal_address = &decimal;
	double *precise_decimal_address = &precise_decimal;

	printf("\nAddresses Stored in Pointers:\n");

	printf("number_address:          %p\n", (void *)number_address);
	printf("character_address:       %p\n", (void *)character_address);
	printf("decimal_address:         %p\n", (void *)decimal_address);
	printf("precise_decimal_address: %p\n", (void *)precise_decimal_address);

	return 0;
}
