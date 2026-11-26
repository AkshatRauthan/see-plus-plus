#include <stdio.h>
#include <stdlib.h>

// Represents a student and their basic information.
struct Student {
    int id;
    int age;
    float marks;
};

// Allocates a contiguous array of Student structures.
struct Student *CreateStudents(size_t count) {
    // Allocate memory for count consecutive Student structures.
    struct Student *students = calloc(count, sizeof *students);

    if (students == NULL) {
        return NULL;
    }

    // Initialize each student's information.
    for (size_t i = 0; i < count; i++) {
        students[i].id = (int)(i + 1) * 100;
        students[i].age = 18 + (int)i;
        students[i].marks = 75.0f + (float)(i * 5);
    }

    return students;
}

// Allocates an array of pointers and separately allocates each Student.
struct Student **CreateStudentPointers(size_t count) {
    // Allocate an array of Student pointers.
    struct Student **students = calloc(count, sizeof *students);

    if (students == NULL) {
        return NULL;
    }

    // Allocate each Student structure separately.
    for (size_t i = 0; i < count; i++) {
        students[i] = malloc(sizeof *students[i]);

        // Clean up earlier allocations if one allocation fails.
        if (students[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(students[j]);
            }

            free(students);
            return NULL;
        }

        // Initialize the allocated Student structure.
        students[i]->id = (int)(i + 1) * 100;
        students[i]->age = 18 + (int)i;
        students[i]->marks = 75.0f + (float)(i * 5);
    }

    return students;
}

int main(void) {
    const size_t count = 3;

    // Approach 1: Allocate a contiguous array of structures.
    struct Student *students = CreateStudents(count);

    if (students == NULL) {
        fprintf(stderr, "Student array allocation failed.\n");
        return 1;
    }

    printf("Array of Structures:\n");

    for (size_t i = 0; i < count; i++) {
        printf(
            "Student %zu: ID=%d, Age=%d, Marks=%.2f, Address=%p\n",
            i,
            students[i].id,
            students[i].age,
            students[i].marks,
            (void *)&students[i]
        );
    }

    // Modify a structure directly through array indexing.
    students[1].marks = 99.0f;

    printf("\nAfter Modifying Second Student:\n");
    printf("Marks: %.2f\n", students[1].marks);

    // Release the entire contiguous structure array.
    free(students);
    students = NULL;

    // Approach 2: Allocate an array of structure pointers.
    struct Student **studentPointers = CreateStudentPointers(count);

    if (studentPointers == NULL) {
        fprintf(stderr, "Student pointer array allocation failed.\n");
        return 1;
    }

    printf("\nArray of Pointers to Structures:\n");

    for (size_t i = 0; i < count; i++) {
        printf(
            "Student %zu: ID=%d, Age=%d, Marks=%.2f, Address=%p\n",
            i,
            studentPointers[i]->id,
            studentPointers[i]->age,
            studentPointers[i]->marks,
            (void *)studentPointers[i]
        );
    }

    // Modify a structure through its individual pointer.
    studentPointers[1]->marks = 99.0f;

    printf("\nAfter Modifying Second Student:\n");
    printf("Marks: %.2f\n", studentPointers[1]->marks);

    // Release each individually allocated Student structure.
    for (size_t i = 0; i < count; i++) {
        free(studentPointers[i]);
    }

    // Release the array containing the structure pointers.
    free(studentPointers);
    studentPointers = NULL;

    return 0;
}
