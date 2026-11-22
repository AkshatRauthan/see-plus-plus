#include <stddef.h>
#include <stdio.h>

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50};

    int *start = numbers;
    int *end = numbers + 5;

    // 1. Valid pointer arithmetic within an array.
    int *second = start + 1;

    printf("Second element: %d\n", *second);

    // 2. A one-past-the-end pointer can be formed.
    printf("Distance: %td elements\n", end - start);

    // It can also be compared with pointers into the same array.
    printf("End is after last element: %s\n",
           end > start + 4 ? "true" : "false");

    // 3. Moving backwards within the array.
    int *last = end - 1;

    printf("Last element: %d\n", *last);

    // 4. Valid traversal using a one-past-the-end boundary.
    printf("\nArray traversal:\n");

    for (int *current = start; current != end; current++) {
        printf("%d ", *current);
    }

    printf("\n");

    // 5. Valid pointer subtraction.
    ptrdiff_t index = last - start;

    printf("\nLast element index: %td\n", index);

    return 0;
}
