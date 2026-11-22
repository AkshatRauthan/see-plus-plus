#include <stddef.h>
#include <stdio.h>

int main(void) {
	int numbers[] = {10, 20, 30, 40, 50};

	int *start = numbers;
	int *middle = numbers + 2;
	int *end = numbers + 5;

	// Pointer addition: move forward by an element offset.
	printf("start:  %d\n", *start);
	printf("middle: %d\n", *middle);

	// Pointer subtraction: calculate the distance between pointers.
	// Both pointers must refer to the same array object,
	// or one position past that array.
	ptrdiff_t distance = end - start;
	ptrdiff_t middle_offset = middle - start;

	printf("\nDistance from start to end: %td elements\n", distance);
	printf("Offset of middle from start: %td elements\n", middle_offset);

	// Pointer subtraction can also be used to calculate
	// an element's index within an array.
	for (int *current = start; current < end; current++) {
		ptrdiff_t index = current - start;

		printf("numbers[%td] = %d\n", index, *(start + index));
	}

	// Pointer addition works with offsets in either direction,
	// provided the resulting pointer remains within the array
	// or points exactly one position past its end.
	int *last = end - 1;

	printf("\nLast element: %d\n", *last);

	return 0;
}
