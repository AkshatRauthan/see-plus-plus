#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    int (*rowPtr)[4] = matrix;
    int *elementPtr = matrix[0];
    int (*wholeArrayPtr)[3][4] = &matrix;

    printf("=== Array and Pointer Types ===\n");
    printf("matrix:             %p\n", (void *)matrix);
    printf("matrix[0]:          %p\n", (void *)matrix[0]);
    printf("&matrix[0]:         %p\n", (void *)&matrix[0]);
    printf("&matrix[0][0]:      %p\n", (void *)&matrix[0][0]);
    printf("rowPtr:             %p\n", (void *)rowPtr);
    printf("elementPtr:         %p\n", (void *)elementPtr);
    printf("wholeArrayPtr:      %p\n", (void *)wholeArrayPtr);

    printf("\n=== Pointer Sizes ===\n");
    printf("sizeof(matrix):            %zu\n", sizeof(matrix));
    printf("sizeof(matrix[0]):         %zu\n", sizeof(matrix[0]));
    printf("sizeof(matrix[0][0]):      %zu\n", sizeof(matrix[0][0]));
    printf("sizeof(rowPtr):            %zu\n", sizeof(rowPtr));
    printf("sizeof(*rowPtr):           %zu\n", sizeof(*rowPtr));
    printf("sizeof(elementPtr):        %zu\n", sizeof(elementPtr));
    printf("sizeof(*elementPtr):       %zu\n", sizeof(*elementPtr));
    printf("sizeof(wholeArrayPtr):     %zu\n", sizeof(wholeArrayPtr));
    printf("sizeof(*wholeArrayPtr):    %zu\n", sizeof(*wholeArrayPtr));

    printf("\n=== Row Pointer Arithmetic ===\n");
    printf("rowPtr:       %p\n", (void *)rowPtr);
    printf("rowPtr + 1:   %p\n", (void *)(rowPtr + 1));
    printf("rowPtr + 2:   %p\n", (void *)(rowPtr + 2));
    printf("rowPtr + 3:   %p (one-past)\n", (void *)(rowPtr + 3));

    printf("\n=== Element Pointer Arithmetic ===\n");
    printf("elementPtr:       %p\n", (void *)elementPtr);
    printf("elementPtr + 1:   %p\n", (void *)(elementPtr + 1));
    printf("elementPtr + 2:   %p\n", (void *)(elementPtr + 2));
    printf("elementPtr + 3:   %p\n", (void *)(elementPtr + 3));
    printf("elementPtr + 4:   %p (one-past row 0)\n", (void *)(elementPtr + 4));

    printf("\n=== Dereferencing Different Pointer Types ===\n");
    printf("rowPtr[0][0]:             %d\n", rowPtr[0][0]);
    printf("rowPtr[1][0]:             %d\n", rowPtr[1][0]);
    printf("elementPtr[0]:             %d\n", elementPtr[0]);
    printf("elementPtr[3]:             %d\n", elementPtr[3]);
    printf("(*wholeArrayPtr)[1][2]:    %d\n", (*wholeArrayPtr)[1][2]);

    printf("\n=== Pointer Advancement ===\n");
    printf("rowPtr + 1 points to row: %p\n", (void *)(rowPtr + 1));
    printf("elementPtr + 1 points to:  %p\n", (void *)(elementPtr + 1));
    printf("wholeArrayPtr + 1 points to: %p\n",
           (void *)(wholeArrayPtr + 1));

    return 0;
}
