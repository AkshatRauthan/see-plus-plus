#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};
	int other[] = {100, 200, 300, 400, 500};

	int *ptr = numbers;

	printf("=== Array and Pointer ===\n");
	printf("numbers[0]: %d\n", numbers[0]);
	printf("*ptr:       %d\n", *ptr);

	printf("\n=== Addresses ===\n");
	printf("numbers:    %p\n", (void *)numbers);
	printf("&numbers:   %p\n", (void *)&numbers);
	printf("ptr:       %p\n", (void *)ptr);
	printf("&ptr:      %p\n", (void *)&ptr);

	printf("\n=== Pointer Reassignment ===\n");
	ptr = other;

	printf("ptr:       %p\n", (void *)ptr);
	printf("*ptr:      %d\n", *ptr);
	printf("ptr[1]:   %d\n", ptr[1]);

	printf("\n=== Array Modification ===\n");
	numbers[0] = 999;

	printf("numbers[0]: %d\n", numbers[0]);
	printf("*ptr:       %d\n", *ptr);

	printf("\n=== Pointer Modification ===\n");
	*ptr = 888;

	printf("other[0]:   %d\n", other[0]);
	printf("*ptr:       %d\n", *ptr);

	return 0;
}
