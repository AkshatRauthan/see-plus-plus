#include <stdio.h>

int main(void) {
	int first[] = {10, 20, 30, 40, 50};
	int second[] = {100, 200, 300, 400, 500};

	int *ptr = first;

	printf("=== Initial State ===\n");
	printf("ptr points to first:\n");
	printf("*ptr = %d\n", *ptr);
	printf("ptr[1] = %d\n", ptr[1]);

	printf("\n=== Modifying Array Through Pointer ===\n");
	*ptr = 999;
	ptr[1] = 888;

	printf("first[0] = %d\n", first[0]);
	printf("first[1] = %d\n", first[1]);

	printf("\n=== Pointer Reassignment ===\n");
	ptr = second;

	printf("*ptr = %d\n", *ptr);
	printf("ptr[1] = %d\n", ptr[1]);

	printf("\n=== Modifying Second Array Through Pointer ===\n");
	*ptr = 777;
	*(ptr + 1) = 666;

	printf("second[0] = %d\n", second[0]);
	printf("second[1] = %d\n", second[1]);

	printf("\n=== Both Arrays ===\n");

	printf("first: ");
	for (size_t i = 0; i < 5; i++) {
		printf("%d ", first[i]);
	}

	printf("\nsecond: ");
	for (size_t i = 0; i < 5; i++) {
		printf("%d ", second[i]);
	}

	printf("\n");

	return 0;
}
