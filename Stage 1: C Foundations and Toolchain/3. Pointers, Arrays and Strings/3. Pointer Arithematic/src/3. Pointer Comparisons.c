#include <stdio.h>

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};

    int *first = &numbers[0];
    int *second = &numbers[1];
    int *same_as_first = numbers;
    int *last = &numbers[4];
    int *end = numbers + 5;

    // 1. Equality comparison
    printf("first == same_as_first: %s\n",
           first == same_as_first ? "true" : "false");

    printf("first == second: %s\n",
           first == second ? "true" : "false");

    // 2. Inequality comparison
    printf("\nfirst != second: %s\n",
           first != second ? "true" : "false");

    // 3. Relational comparisons
    // Both pointers refer to elements of the same array.
    printf("\nfirst < second: %s\n",
           first < second ? "true" : "false");

    printf("last > second: %s\n",
           last > second ? "true" : "false");

    printf("first <= same_as_first: %s\n",
           first <= same_as_first ? "true" : "false");

    printf("last >= second: %s\n",
           last >= second ? "true" : "false");

    // 4. Comparing against the one-past-the-end pointer
    printf("\nend > last: %s\n",
           end > last ? "true" : "false");

    // 5. Pointer comparisons in array traversal
    printf("\nArray elements:\n");

    for (int *current = first; current < end; current++) {
        printf("%d\n", *current);
    }

    return 0;
}
