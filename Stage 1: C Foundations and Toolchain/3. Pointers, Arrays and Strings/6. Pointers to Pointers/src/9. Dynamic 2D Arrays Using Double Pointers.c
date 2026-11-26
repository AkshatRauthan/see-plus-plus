#include <stdio.h>
#include <stdlib.h>

// Allocates a 2D integer array with independently allocated rows.
int AllocateMatrix(int ***matrix, size_t rows, size_t cols) {
	// Allocate an array of pointers, one for each row.
	int **memory = calloc(rows, sizeof *memory);

	// Return failure if the row-pointer allocation failed.
	if (memory == NULL) {
		return 0;
	}

	// Allocate memory for each individual row.
	for (size_t i = 0; i < rows; i++) {
		memory[i] = calloc(cols, sizeof *memory[i]);

		// Release previously allocated rows if allocation fails.
		if (memory[i] == NULL) {
			for (size_t j = 0; j < i; j++) {
				free(memory[j]);
			}

			free(memory);
			return 0;
		}
	}

	// Store the allocated matrix address in the caller's pointer.
	*matrix = memory;

	return 1;
}

int main(void) {
	const size_t rows = 3;
	const size_t cols = 4;

	// Initially, the matrix pointer doesn't refer to an allocation.
	int **matrix = NULL;

	// Allocate the matrix and update the caller's pointer.
	if (!AllocateMatrix(&matrix, rows, cols)) {
		fprintf(stderr, "Failed to allocate matrix.\n");
		return 1;
	}

	// Initialize the matrix with sample values.
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			matrix[i][j] = (int)(i * cols + j + 1);
		}
	}

	// Display the matrix using normal 2D array indexing.
	printf("Matrix:\n");

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			printf("%4d", matrix[i][j]);
		}

		printf("\n");
	}

	// Modify an individual element.
	matrix[1][2] = 999;

	printf("\nAfter Modification:\n");

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			printf("%4d", matrix[i][j]);
		}

		printf("\n");
	}

	// Free each independently allocated row.
	for (size_t i = 0; i < rows; i++) {
		free(matrix[i]);
	}

	// Free the array containing the row pointers.
	free(matrix);

	// Avoid retaining a dangling pointer.
	matrix = NULL;

	return 0;
}
