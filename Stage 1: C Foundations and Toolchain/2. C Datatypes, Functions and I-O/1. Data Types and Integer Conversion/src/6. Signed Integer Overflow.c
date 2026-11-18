
#include <limits.h>
#include <stdio.h>

int main(void) {
	int value = INT_MAX;

	/* Intentionally triggers signed integer overflow. */
	value += 1;

	printf("Result: %d\n", value);

	return 0;
}
