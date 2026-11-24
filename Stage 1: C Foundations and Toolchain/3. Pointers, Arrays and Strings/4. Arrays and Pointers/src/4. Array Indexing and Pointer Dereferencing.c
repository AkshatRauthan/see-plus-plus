#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};
	int *ptr = numbers;

	printf("=== Array Indexing ===\n");

	for (int i = 0; i < 5; i++) {
		printf("numbers[%d] = %d\n", i, numbers[i]);
	}

	printf("\n=== Pointer Dereferencing ===\n");

	for (int i = 0; i < 5; i++) {
		printf("*(ptr + %d) = %d\n", i, *(ptr + i));
	}

	printf("\n=== Equivalent Expressions ===\n");

	printf("numbers[2]    = %d\n", numbers[2]);
	printf("*(numbers + 2) = %d\n", *(numbers + 2));
	printf("ptr[2]         = %d\n", ptr[2]);
	printf("*(ptr + 2)     = %d\n", *(ptr + 2));
	printf("2[numbers]     = %d\n", 2 [numbers]);

	printf("\n=== Modifying Through Different Expressions ===\n");

	numbers[1] = 200;
	*(ptr + 2) = 300;
	ptr[3] = 400;

	for (int i = 0; i < 5; i++) {
		printf("numbers[%d] = %d\n", i, numbers[i]);
	}

	return 0;
}
