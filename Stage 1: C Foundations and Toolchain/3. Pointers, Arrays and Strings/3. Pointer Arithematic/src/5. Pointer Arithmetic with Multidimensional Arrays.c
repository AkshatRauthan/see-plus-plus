#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {
			10, 20, 30, 40
		},
        {
			50, 60, 70, 80
		},
        {
			90, 100, 110, 120
		}
    };

    // The array name decays to a pointer to its first row.
    int (*row)[4] = matrix;

    // 1. Accessing elements using pointer arithmetic.
    printf("First row:\n");

    for (int column = 0; column < 4; column++) {
        printf("%d ", *(*row + column));
    }

    // 2. Moving between rows.
    row++;

    printf("\n\nSecond row:\n");

    for (int column = 0; column < 4; column++) {
        printf("%d ", *(*row + column));
    }

    // 3. Accessing an element using row and column offsets.
    int value = *(*(matrix + 2) + 1);

    printf("\n\nmatrix[2][1] = %d\n", value);

    // 4. Equivalent pointer expressions.
    printf("\nEquivalent expressions:\n");
    printf("matrix[1][2]          = %d\n", matrix[1][2]);
    printf("*(*(matrix + 1) + 2) = %d\n", *(*(matrix + 1) + 2));

    // 5. Traversing the entire matrix.
    printf("\nEntire matrix:\n");

    for (int (*current_row)[4] = matrix;
        current_row < matrix + 3;
        current_row++) {

        for (int *current_column = *current_row;
             current_column < *current_row + 4;
             current_column++) {

            printf("%4d", *current_column);
        }

        printf("\n");
    }

    return 0;
}
