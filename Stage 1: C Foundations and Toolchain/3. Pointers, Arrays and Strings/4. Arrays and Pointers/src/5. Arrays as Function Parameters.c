#include <stdio.h>

void PrintArray(int arr[], size_t length);
void PrintArrayUsingPointer(int *ptr, size_t length);
void ModifyArray(int arr[], size_t length);
void PrintParameterSize(int arr[]);

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};
	size_t length = sizeof(numbers) / sizeof(numbers[0]);

	printf("=== Original Array ===\n");
	PrintArray(numbers, length);

	printf("\n=== Array Passed to Pointer Parameter ===\n");
	PrintArrayUsingPointer(numbers, length);

	printf("\n=== Modifying Array Inside Function ===\n");
	ModifyArray(numbers, length);
	PrintArray(numbers, length);

	printf("\n=== sizeof Inside Function ===\n");
	PrintParameterSize(numbers);

	printf("\n=== Main Scope Size ===\n");
	printf("sizeof(numbers): %zu bytes\n", sizeof(numbers));

	return 0;
}

void PrintArray(int arr[], size_t length) {
	printf("Array elements: ");

	for (size_t i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

void PrintArrayUsingPointer(int *ptr, size_t length) {
	printf("Array elements: ");

	for (size_t i = 0; i < length; i++) {
		printf("%d ", *(ptr + i));
	}

	printf("\n");
}

void ModifyArray(int arr[], size_t length) {
	for (size_t i = 0; i < length; i++) {
		arr[i] *= 2;
	}
}

void PrintParameterSize(int arr[]) {
	printf("sizeof(arr): %zu bytes\n", sizeof(arr));
}
