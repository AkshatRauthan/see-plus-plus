#include <stdio.h>
#include <stdlib.h>

// Represents a student and their basic information.
struct Student {
	int id;
	int age;
	float marks;
};

// Allocates a Student structure and updates the caller's pointer.
int CreateStudent(struct Student **student, int id, int age, float marks) {
	// Allocate memory for one Student structure.
	struct Student *memory = malloc(sizeof *memory);

	// Return failure if allocation was unsuccessful.
	if (memory == NULL) {
		return 0;
	}

	// Initialize the structure members.
	memory->id = id;
	memory->age = age;
	memory->marks = marks;

	// Update the caller's structure pointer.
	*student = memory;

	return 1;
}

// Modifies the caller's pointer to refer to a different student.
int ReplaceStudent(struct Student **student, int id, int age, float marks) {
	// Allocate a replacement structure first.
	struct Student *replacement = malloc(sizeof *replacement);

	// Preserve the original allocation if replacement fails.
	if (replacement == NULL) {
		return 0;
	}

	// Initialize the replacement structure.
	replacement->id = id;
	replacement->age = age;
	replacement->marks = marks;

	// Release the previous structure allocation.
	free(*student);

	// Update the caller's pointer.
	*student = replacement;

	return 1;
}

int main(void) {
	// Initially, no Student structure is allocated.
	struct Student *student = NULL;

	// Allocate the first student.
	if (!CreateStudent(&student, 101, 20, 87.5f)) {
		fprintf(stderr, "Student allocation failed.\n");
		return 1;
	}

	// Display the first student's information.
	printf("Original Student:\n");
	printf("Address: %p\n", (void *)student);
	printf("ID: %d\n", student->id);
	printf("Age: %d\n", student->age);
	printf("Marks: %.2f\n", student->marks);

	// Modify a member through the structure pointer.
	student->marks = 92.5f;

	printf("\nAfter Modifying Marks:\n");
	printf("Marks: %.2f\n", student->marks);

	// Replace the allocated structure through a double pointer.
	if (!ReplaceStudent(&student, 102, 22, 95.0f)) {
		fprintf(stderr, "Student replacement failed.\n");
		free(student);
		return 1;
	}

	// The caller's pointer now refers to the replacement.
	printf("\nAfter Replacing Student:\n");
	printf("Address: %p\n", (void *)student);
	printf("ID: %d\n", student->id);
	printf("Age: %d\n", student->age);
	printf("Marks: %.2f\n", student->marks);

	// Release the final structure allocation.
	free(student);
	student = NULL;

	return 0;
}
