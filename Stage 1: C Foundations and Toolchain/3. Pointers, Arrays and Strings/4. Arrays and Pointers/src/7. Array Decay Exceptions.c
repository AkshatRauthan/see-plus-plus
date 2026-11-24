#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};

	printf("=== Normal Array Expression ===\n");
	printf("numbers: %p\n", (void *)numbers);
	printf("numbers + 1: %p\n", (void *)(numbers + 1));

	printf("\n=== Exception 1: sizeof ===\n");
	printf("sizeof(numbers): %zu bytes\n", sizeof(numbers));
	printf("sizeof(numbers[0]): %zu bytes\n", sizeof(numbers[0]));

	printf("\n=== Exception 2: Unary & ===\n");
	printf("numbers: %p\n", (void *)numbers);
	printf("&numbers: %p\n", (void *)&numbers);
	printf("&numbers + 1: %p\n", (void *)(&numbers + 1));
	printf("&numbers[0] + 1: %p\n", (void *)(&numbers[0] + 1));
	printf("&numbers[0] + 2: %p\n", (void *)(&numbers[2] + 1));

	printf("\n=== Exception 3: Array Initialization ===\n");
	int copy[] = {10, 20, 30, 40, 50};

	printf("numbers[0]: %d\n", numbers[0]);
	printf("copy[0]: %d\n", copy[0]);

	copy[0] = 999;

	printf("After modifying copy:\n");
	printf("numbers[0]: %d\n", numbers[0]);
	printf("copy[0]: %d\n", copy[0]);

	return 0;
}
