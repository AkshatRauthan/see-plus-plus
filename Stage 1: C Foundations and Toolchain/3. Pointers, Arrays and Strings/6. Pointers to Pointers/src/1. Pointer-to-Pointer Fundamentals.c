#include <stdio.h>

int main(void) {
	int value = 100;

	int *ptr = &value;
	int **doublePtr = &ptr;

	printf("Variable:\n");
	printf("value: %d\n", value);
	printf("Address of value: %p\n\n", (void *)&value);

	printf("Single Pointer:\n");
	printf("ptr: %p\n", (void *)ptr);
	printf("*ptr: %d\n", *ptr);
	printf("Address of ptr: %p\n\n", (void *)&ptr);

	printf("Double Pointer:\n");
	printf("doublePtr: %p\n", (void *)doublePtr);
	printf("*doublePtr: %p\n", (void *)*doublePtr);
	printf("**doublePtr: %d\n", **doublePtr);
	printf("Address of doublePtr: %p\n", (void *)&doublePtr);

	return 0;
}
