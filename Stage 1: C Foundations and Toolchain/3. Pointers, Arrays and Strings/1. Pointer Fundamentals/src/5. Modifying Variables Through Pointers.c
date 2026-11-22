#include <stdio.h>

/*
 * Demonstrates ordinary pass-by-value.
 *
 * The function receives a copy of the integer.
 * Modifying the copy does not affect the caller's variable.
 */
static void increment_copy(int value) { value++; }

/*
 * Increments the integer through its pointer.
 *
 * The pointer contains the address of the caller's variable.
 * Dereferencing it allows the original object to be modified.
 */
static int increment_value(int *value) {
	if (value == NULL) {
		return -1;
	}

	(*value)++;

	return 0;
}

/*
 * Assigns a new value to the caller's variable.
 */
static int set_value(int *value, int new_value) {
	if (value == NULL) {
		return -1;
	}

	*value = new_value;

	return 0;
}

int main(void) {
	int number = 10;

	// Ordinary pass-by-value.
	printf("Before increment_copy(): %d\n", number);

	increment_copy(number);

	// The original variable remains unchanged.
	printf("After increment_copy():  %d\n", number);

	// Modify the original variable through its address.
	printf("\nBefore increment_value(): %d\n", number);

	if (increment_value(&number) != 0) {
		fprintf(stderr, "Failed to increment value.\n");
		return 1;
	}

	printf("After increment_value():  %d\n", number);

	// Assign a completely new value through a pointer.
	printf("\nBefore set_value(): %d\n", number);

	if (set_value(&number, 100) != 0) {
		fprintf(stderr, "Failed to set value.\n");
		return 1;
	}

	printf("After set_value():  %d\n", number);

	return 0;
}
