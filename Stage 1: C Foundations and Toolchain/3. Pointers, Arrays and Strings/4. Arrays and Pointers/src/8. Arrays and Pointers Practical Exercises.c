#include <stddef.h>
#include <stdio.h>

void PrintArray(const int *ptr, size_t length);
int SumArray(const int *ptr, size_t length);
void ModifyArray(int *ptr, size_t length);
void DemonstratePointerArithmetic(int *ptr, size_t length);

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};
	int other[] = {100, 200, 300, 400, 500};

	size_t length = sizeof(numbers) / sizeof(numbers[0]);

	printf("=== 1. Array and Pointer ===\n");
	int *ptr = numbers;

	printf("numbers[0]: %d\n", numbers[0]);
	printf("*ptr:       %d\n", *ptr);
	printf("ptr[1]:     %d\n", ptr[1]);

	printf("\n=== 2. Array Size ===\n");
	printf("Array bytes: %zu\n", sizeof(numbers));
	printf("Element bytes: %zu\n", sizeof(numbers[0]));
	printf("Element count: %zu\n", length);
	printf("Pointer bytes: %zu\n", sizeof(ptr));

	printf("\n=== 3. Pointer Arithmetic ===\n");
	DemonstratePointerArithmetic(numbers, length);

	printf("\n=== 4. Pointer Reassignment ===\n");
	ptr = other;
	printf("*ptr after reassignment: %d\n", *ptr);
	printf("ptr[2]: %d\n", ptr[2]);

	printf("\n=== 5. Modifying Through Pointer ===\n");
	*ptr = 999;
	ptr[1] = 888;
	PrintArray(other, length);

	printf("\n=== 6. Array Passed to Function ===\n");
	printf("Sum of numbers: %d\n", SumArray(numbers, length));
	printf("Sum of other: %d\n", SumArray(other, length));

	printf("\n=== 7. Modifying Array in Function ===\n");
	ModifyArray(numbers, length);
	PrintArray(numbers, length);

	printf("\n=== 8. Pointer to Entire Array ===\n");
	int(*arrayPtr)[5] = &numbers;

	printf("First element: %d\n", (*arrayPtr)[0]);
	printf("Third element: %d\n", (*arrayPtr)[2]);
	printf("Next array address: %p\n", (void *)(arrayPtr + 1));
	printf("Current array address: %p\n", (void *)arrayPtr);

	printf("\n=== 9. One-Past-the-End ===\n");
	int *end = numbers + length;

	printf("Last element: %d\n", *(end - 1));
	printf("Distance: %td elements\n", end - numbers);

	return 0;
}

void PrintArray(const int *ptr, size_t length) {
	for (size_t i = 0; i < length; i++) {
		printf("%d ", ptr[i]);
	}

	printf("\n");
}

int SumArray(const int *ptr, size_t length) {
	int sum = 0;

	for (size_t i = 0; i < length; i++) {
		sum += ptr[i];
	}

	return sum;
}

void ModifyArray(int *ptr, size_t length) {
	for (size_t i = 0; i < length; i++) {
		ptr[i] += 5;
	}
}

void DemonstratePointerArithmetic(int *ptr, size_t length) {
	for (size_t i = 0; i < length; i++) {
		printf("ptr + %zu = %d\n", i, *(ptr + i));
	}
}
