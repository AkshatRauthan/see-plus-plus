#include <stddef.h>
#include <stdio.h>

int main(void) {
	int numbers[] = {12, 24, 36, 48, 60, 72};

	int *start = numbers;
	int *end = numbers + 6;

	// 1. Forward traversal using pointer arithmetic.
	printf("Forward traversal:\n");

	for (int *current = start; current < end; current++) {
		printf("%d ", *current);
	}

	// 2. Reverse traversal.
	// Start at the last valid element, not at end.
	printf("\n\nReverse traversal:\n");

	for (int *current = end; current != start;) {
		current--;
		printf("%d ", *current);
	}

	// 3. Accessing an element using an offset.
	int offset = 3;
	int *selected = start + offset;

	printf("\n\nElement at offset %d: %d\n", offset, *selected);

	// 4. Finding an element's index using pointer subtraction.
	ptrdiff_t index = selected - start;

	printf("Selected element index: %td\n", index);

	// 5. Calculating the number of elements between pointers.
	int *first = &numbers[1];
	int *last = &numbers[4];

	ptrdiff_t distance = last - first;

	printf("\nDistance between numbers[1] and numbers[4]: %td\n", distance);

	// 6. Comparing pointers within the same array.
	printf("first < last: %s\n", first < last ? "true" : "false");

	// 7. Using one-past-the-end as a boundary.
	printf("\nElements before the boundary:\n");

	for (int *current = start; current != end; current++) {
		printf("%d ", *current);
	}

	printf("\n");

	return 0;
}
