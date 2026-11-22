#include <stdio.h>

typedef struct {
	int id;
	double salary;
	char grade;
} Employee;

int main(void) {
	Employee employees[] = {
		{101, 45000.0, 'A'}, 
		{102, 52000.0, 'B'}, 
		{103, 61000.0, 'A'}
	};

	Employee *current = employees;

	// 1. Accessing structure members through a pointer.
	printf("First employee:\n");
	printf("ID: %d\n", current->id);
	printf("Salary: %.2f\n", current->salary);
	printf("Grade: %c\n", current->grade);

	// 2. Incrementing a structure pointer.
	// Advances by sizeof(Employee) bytes conceptually.
	current++;

	printf("\nSecond employee:\n");
	printf("ID: %d\n", current->id);
	printf("Salary: %.2f\n", current->salary);
	printf("Grade: %c\n", current->grade);

	// 3. Accessing the third structure using pointer addition.
	Employee *third = employees + 2;

	printf("\nThird employee:\n");
	printf("ID: %d\n", third->id);
	printf("Salary: %.2f\n", third->salary);
	printf("Grade: %c\n", third->grade);

	// 4. Traversing the structure array.
	Employee *end = employees + 3;

	printf("\nAll employees:\n");

	for (Employee *ptr = employees; ptr < end; ptr++) {
		printf("ID: %d | Salary: %.2f | Grade: %c\n", ptr->id, ptr->salary, ptr->grade);
	}

	return 0;
}
