#include <stdio.h>

void modify(int *ptr) {
	printf("Inside modify()\n");
	*ptr = 100; // Deliberate segmentation fault => Modifying null pointer's
				// unederlying value
}

void calculate(int *value) {
	printf("Inside calculate()\n");

	int multiplier = 5;
	int result = *value * multiplier;

	printf("Intermediate result: %d\n", result);

	modify(NULL);

	*value = result;
}

void process(void) {
	printf("Inside process()\n");

	int number = 10;

	calculate(&number);

	printf("Final result: %d\n", number);
}

int main(void) {
	printf("Program started\n");

	process();

	printf("Program finished\n");

	return 0;
}
