#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"
#include "utils.h"
#include "console.h"

StudentLinkedList *head = NULL;
StudentLinkedList *tail = NULL;
int numberOfStudents = 0;

bool askUserForName(char *name, int length) {
    getString("Enter the name of the student: ", name, length);
    return checkString(name, ALPHA_FLAG | SPACE_FLAG);
}

bool askUserForSurname(char *surname, int length) {
    getString("Enter the surname of the student: ", surname, length);
    return checkString(surname, ALPHA_FLAG | SPACE_FLAG);
}

bool askUserForMaster(char *master, int length) {
    getString("Enter the name of the master: ", master, length);
    return checkString(master, ALPHA_FLAG | NUMBER_FLAG);
}


bool askUserForAge(int *age) {
    *age = getInt("Enter the student's age: ");
    return checkAge(*age);
}


bool askUserForGender(char *gender) {
    char *genderOptions[] = {"Male", "Female"};
    int selectedOption = getOption(
            "Enter the student's gender",
            (const char **) genderOptions,
            sizeof(genderOptions) / sizeof(char *)
    );
    *gender = selectedOption == 1 ? 'M' : 'F';
}


bool checkName(const char *name) {
    return checkString(name, ALPHA_FLAG | SPACE_FLAG);
}

bool checkSurname(const char *surname) {
    return checkString(surname, ALPHA_FLAG | SPACE_FLAG);
}

bool checkMaster(const char *master) {
    return checkString(master, ALPHA_FLAG | NUMBER_FLAG);
}

bool checkAge(int age) {
    return age >= 0 && age <= 100;
}

bool checkGender(char gender) {
    return gender == 'M' || gender == 'F';
}

bool addStudentRecord(char *name, char *surname, char *master, int age, char gender) {
    StudentLinkedList *newStudent = (StudentLinkedList *) malloc(sizeof(StudentLinkedList));
    if (newStudent == NULL) {
        printf("Error: Memory allocation failed\n");
        return false;
    }
    newStudent->student.id = tail == NULL ? 1 : tail->student.id + 1;
    strncpy(newStudent->student.name, name, MAX_NAME_LENGTH);
    strncpy(newStudent->student.surname, surname, MAX_SURNAME_LENGTH);
    strncpy(newStudent->student.master, master, MAX_MASTER_LENGTH);
    newStudent->student.age = age;
    newStudent->student.gender = gender;
    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
        tail = newStudent;
    } else {
        tail->next = newStudent;
        tail = newStudent;
    }
    numberOfStudents++;
    return true;
}

bool deleteStudentRecord(int id) {
    StudentLinkedList *current = head;
    StudentLinkedList *previous = NULL;

    while (current != NULL) {
        // Iterate through the linked list and find the student with the given id
        if (current->student.id != id) {
            previous = current;
            current = current->next;
            continue;
        }

        // Dealing the case where the student is the first one in the linked list
        if (previous == NULL) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
        numberOfStudents--;
        return true;
    }

    return false;
}

void deleteLinkedListContent() {
    StudentLinkedList *current = head;
    while (current != NULL) {
        StudentLinkedList *next = current->next;
        free(current);
        current = next;
    }
}

bool createStudentFromString(const char *line) {
    int id;
    char name[30];
    char surname[30];
    char master[30];
    int age;
    char gender;

    char separator[] = " ";
    int numFieldRead = 0;

    char *strToken = strtok(line, separator);
    while (strToken != NULL) {
        numFieldRead++;
        if (numFieldRead == 1) {
            char *endptr;
            id = (int) strtol(strToken, &endptr, 10);
            if (*endptr != '\0') {
                return false;
            }
        } else if (numFieldRead == 2) {
            strncpy(name, strToken, 30);
            if (!checkName(name)) {
                return false;
            }
        } else if (numFieldRead == 3) {
            strncpy(surname, strToken, 30);
            if (!checkSurname(surname)) {
                return false;
            }
        } else if (numFieldRead == 4) {
            strncpy(master, strToken, 30);
            if (!checkMaster(master)) {
                return false;
            }
        } else if (numFieldRead == 5) {
            char *endPtr;
            age = (int) strtol(strToken, &endPtr, 10);
            if (*endPtr != '\0') {
                return false;
            }
            // Checking that age is between 0 and 100
            if (!checkAge(age)) {
                return false;
            }
        } else if (numFieldRead == 6) {
            gender = strToken[0];
            if (!checkGender(gender)) {
                return false;
            }
        }

        // We ask for the next token
        strToken = strtok(NULL, separator);
    }

    // Checking that all the fields were read
    if (numFieldRead != 6) {
        return false;
    }

    // Adding the student to the linked list
    addStudentRecord(
            name,
            surname,
            master,
            age,
            gender
    );

    return true;
};


int getNumberOfStudentRecords() {
    return numberOfStudents;
}

static void displayStudent(Student student) {
    puts("Student {");
    printf("  id: %d\n", student.id);
    printf("  name: %s\n", student.name);
    printf("  surname: %s\n", student.surname);
    printf("  master: %s\n", student.master);
    printf("  age: %d\n", student.age);
    printf("  gender: %c\n", student.gender);
    puts("}\n");
}

void displayStudentRecords() {
    StudentLinkedList *current = head;
    while (current != NULL) {
        displayStudent(current->student);
        current = current->next;
    }
}

bool saveStudentRecordsToFile(const FILE *file) {
    StudentLinkedList *current = head;
    while (current != NULL) {
        int output = fprintf(
                file, "%d %s %s %s %d %c\n",
                current->student.id,
                current->student.name,
                current->student.surname,
                current->student.master,
                current->student.age,
                current->student.gender);
        if (output < 0) {
            printf("Error: Writing to file failed\n");
            return false;
        }
        current = current->next;
    }
    return true;
}

Student* getStudentRecord(int id) {
    StudentLinkedList *current = head;
    while (current != NULL) {
        if (current->student.id == id) {
            return &current->student;
        }
        current = current->next;
    }
    return NULL;
}

void setStudentName(Student* student, const char *name) {
    strncpy(student->name, name, MAX_NAME_LENGTH);
}

void setStudentSurname(Student* student, const char *surname) {
    strncpy(student->surname, surname, MAX_SURNAME_LENGTH);
}

void setStudentMaster(Student* student, const char *master) {
    strncpy(student->master, master, MAX_MASTER_LENGTH);
}

void setStudentAge(Student* student, int age) {
    student->age = age;
}

void setStudentGender(Student* student, char gender) {
    student->gender = gender;
}