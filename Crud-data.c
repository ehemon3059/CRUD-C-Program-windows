#include <stdio.h>
#include <stdlib.h>  // For using `exit()` function
#include <string.h>

#define FILE_NAME "students.dat"

#define MAX_STUDENTS 10

// Define the structure for a student
typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void createStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    Student newStudent;
    newStudent.id = student_count + 1;
    
    printf("Enter name: ");
    scanf("%s", newStudent.name);
    
    printf("Enter age: ");
    scanf("%d", &newStudent.age);
    
    students[student_count++] = newStudent;

    // Save the updated student list to the file
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);

    printf("Student added successfully!\n");
}

void readStudents() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No students to display (file not found).\n");
        return;
    }

    // Read student data from the file
    student_count = fread(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);

    if (student_count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("ID\tName\t\tAge\n");
    printf("---------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d\t%s\t\t%d\n", students[i].id, students[i].name, students[i].age);
    }
}

void updateStudent() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    if (id <= 0 || id > student_count) {
        printf("Invalid student ID.\n");
        return;
    }

    printf("Enter new name: ");
    scanf("%s", students[id - 1].name);

    printf("Enter new age: ");
    scanf("%d", &students[id - 1].age);

    // Save the updated student list to the file
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);

    printf("Student updated successfully!\n");
}

void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    if (id <= 0 || id > student_count) {
        printf("Invalid student ID.\n");
        return;
    }

    // Shift all students after the deleted one to the left
    for (int i = id - 1; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;

    // Save the updated student list to the file
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);

    printf("Student deleted successfully!\n");
}


void loadData() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        student_count = fread(students, sizeof(Student), MAX_STUDENTS, file);
        fclose(file);
    } else {
        student_count = 0; // No file found, so start with an empty list
    }
}

int main() {
    loadData();  // Load existing student data from file
    
    int choice;

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Create Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createStudent();
                break;
            case 2:
                readStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
