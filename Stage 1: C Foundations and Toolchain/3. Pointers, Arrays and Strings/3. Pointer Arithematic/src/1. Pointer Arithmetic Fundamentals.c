#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};

	int *pointer = numbers;

	printf("Pointer: %p | Value: %d\n", (void *)pointer, *pointer);

	pointer++;

	printf("Pointer: %p | Value: %d\n", (void *)pointer, *pointer);

	pointer++;

	printf("Pointer: %p | Value: %d\n", (void *)pointer, *pointer);

	return 0;
}
