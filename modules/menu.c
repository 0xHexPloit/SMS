#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "console.h"
#include "student.h"
#include "storage.h"
#include "string.h"
#include "path.h"

typedef enum mainMenuOptions {
    LOAD_STUDENTS_FROM_FILE = 1,
    ADD_STUDENT,
    EDIT_STUDENT,
    REMOVE_STUDENT,
    DISPLAY_STUDENTS,
    SAVE_STUDENTS_TO_FILE,
    EXIT
} MainMenuOptions;

static void displayBanner() {
    printf("====================================================\n");
    printf("     Student Management System (TELECOM PARIS)      \n");
    printf("====================================================\n\n");
}

static void displayLoadFileMenu() {
    clearConsole();
    displayBanner();

    char filePath[100];
    getString("Enter the path to the file: ", filePath, 100);

    // Checking if the file exists
    if (checkFileExists(filePath)) {
        if (readLinesFromFile(filePath, createStudentFromString)) {
            printf("The file has been successfully loaded\n");
            int numberOfStudents = getNumberOfStudentRecords();
            printf("%d student(s) have been loaded\n", numberOfStudents);
        } else {
            printf("An error occured while loading the file\n");
        }
    } else {
        printf("Error: File not found\n");
    }

    waitEnterKey();
}

void displayAddStudentMenu() {
    clearConsole();
    displayBanner();

    char name[30];
    char surname[30];
    char master[30];
    int age;
    char gender;

    // Getting the student's name
    if (askUserForName(name, 30) == false) {
        printf("Error: Invalid name\n");
        waitEnterKey();
        return;
    }
    // Getting the student's surname
    if (askUserForSurname(surname, 30) == false) {
        printf("Error: Invalid surname\n");
        waitEnterKey();
        return;
    }
    // Getting the student's master
    if (askUserForMaster(master, 30) == false) {
        printf("Error: Invalid master\n");
        waitEnterKey();
        return;
    }

    // Getting the student's age
    if (askUserForAge(&age) == false) {
        printf("Error: Invalid age\n");
        waitEnterKey();
        return;
    }

    // Getting the student's gender
    if (askUserForGender(&gender) == false) {
        printf("Error: Invalid gender\n");
        waitEnterKey();
        return;
    }

    // Adding the student record to the linked list
    addStudentRecord(name, surname, master, age, gender);

    printf("\nStudent record added\n");
}

static void displayEditStudentMenu() {
    clearConsole();
    displayBanner();

    // Getting the student's id
    int id = getInt("Enter the student's id: ");
    puts("\n");

    // Checking if the student exists
    Student* student;
    if ((student = getStudentRecord(id)) == NULL) {
        printf("Error: Student not found\n");
        waitEnterKey();
        return;
    }

    while (true) {
        // Asking which field to edit
        char *fieldOptions[] = {"Name", "Surname", "Master", "Age", "Gender"};
        int selectedOption = getOption(
                "Which field do you want to edit?",
                (const char **) fieldOptions,
                sizeof(fieldOptions) / sizeof(char *)
        );

        if (selectedOption == 1) {
            // Editing the student's name
            char name[30];
            if (askUserForName(name, 30) == false) {
                printf("Error: Invalid name\n");
                waitEnterKey();
                return;
            }
            setStudentName(student, name);

        } else if (selectedOption == 2) {
            // Editing the student's surname
            char surname[30];
            if (askUserForSurname(surname, 30) == false) {
                printf("Error: Invalid surname\n");
                waitEnterKey();
                return;
            }
            setStudentSurname(student, surname);

        } else if (selectedOption == 3) {
            // Editing the student's master
            char master[30];
            if (askUserForMaster(master, 30) == false) {
                printf("Error: Invalid master\n");
                waitEnterKey();
                return;
            }
            setStudentMaster(student, master);
        } else if (selectedOption == 4) {
            // Editing the student's age
            int age;
            if (askUserForAge(&age) == false) {
                printf("Error: Invalid age\n");
                waitEnterKey();
                return;
            }
            setStudentAge(student, age);
        } else if (selectedOption == 5) {
            // Editing the student's gender
            char gender;
            if (askUserForGender(&gender) == false) {
                printf("Error: Invalid gender\n");
                waitEnterKey();
                return;
            }
            setStudentGender(student, gender);
        }

        // Asking if the user wants to edit a new field
        puts("The student's record has been updated successfully\n");
        char *newFieldOptions[] = {"Yes", "No"};
        int selectedNewFieldOption = getOption(
                "Do you want to edit another field?",
                (const char **) newFieldOptions,
                sizeof(newFieldOptions) / sizeof(char *)
        );
        if (selectedNewFieldOption == 2) break;
    }
}

static void displayRemoveStudentMenu() {
    clearConsole();
    displayBanner();

    int id = getInt("Enter the student's ID: ");
    puts("\n");

    if (deleteStudentRecord(id)) {
        printf("Student record deleted\n");
    } else {
        printf("Student record not found\n");
    }
}

static void displayShowStudentMenu() {
    clearConsole();
    displayBanner();

    int numberOfStudents = getNumberOfStudentRecords();

    printf("Number of students: %d\n\n", numberOfStudents);

    displayStudentRecords();
    waitEnterKey();
}

void displaySaveMenu() {
    clearConsole();
    displayBanner();

    char buffer[100];
    Path filePath;
    bool canExit = false;

    while (!canExit) {
        getString("Enter the path to the file: ", buffer, 100);
        filePath = createPath(buffer);
        Path parentDirectory = getParentDirectory(&filePath);

        if (checkDirectoryExists(pathToString(&parentDirectory))) {
            canExit = true;
            continue;
        }
        printf("Error: Directory not found\n");
    }

    printf("Writing to file: %s\n", pathToString(&filePath));
    if (writeToDisk(pathToString(&filePath), &saveStudentRecordsToFile)) {
        int numberOfStudents = getNumberOfStudentRecords();
        printf("%d student record(s) saved to file\n", numberOfStudents);
    } else {
        printf("Error: Unable to save student records to file\n");
    }

    waitEnterKey();
}

void displayMainMenu() {
    bool exit = false;

    while (!exit) {
        clearConsole();
        displayBanner();
        const char *options[] = {
                "Load students from file",
                "Add student",
                "Edit student",
                "Remove student",
                "Display students",
                "Save students to file",
                "Exit"};

        int selectedOption = getOption(NULL, options, sizeof(options) / sizeof(char *));

        if (selectedOption == LOAD_STUDENTS_FROM_FILE) {
            displayLoadFileMenu();
        } else if (selectedOption == ADD_STUDENT) {
            displayAddStudentMenu();
        } else if (selectedOption == EDIT_STUDENT) {
            displayEditStudentMenu();
        } else if (selectedOption == REMOVE_STUDENT) {
            displayRemoveStudentMenu();
        } else if (selectedOption == DISPLAY_STUDENTS) {
            displayShowStudentMenu();
        } else if (selectedOption == SAVE_STUDENTS_TO_FILE) {
            displaySaveMenu();
        } else if (selectedOption == EXIT) {
            printf("Thank you for using our system! Bye!\n");
            // Free the linked list
            deleteLinkedListContent();
            exit = true;
            continue;
        }

        freezeConsole(1);
    }
}