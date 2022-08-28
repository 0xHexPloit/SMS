#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "menu.h"
#include "console.h"
#include "student.h"
#include "storage.h"

typedef enum mainMenuOptions
{
  LOAD_STUDENTS_FROM_FILE = 1,
  ADD_STUDENT,
  EDIT_STUDENT,
  REMOVE_STUDENT,
  DISPLAY_STUDENTS,
  SAVE_STUDENTS_TO_FILE,
  EXIT
} MainMenuOptions;

static void displayBanner()
{
  printf("====================================================\n");
  printf("     Student Management System (TELECOM PARIS)      \n");
  printf("====================================================\n\n");
}

static void displayLoadFileMenu()
{
  clearConsole();
  displayBanner();

  char filePath[100];

  getString("Enter the path to the file: ", filePath, 100, NO_FLAG);

  // Checking if the file exists
  if (checkFileExists(filePath))
  {
    loadStudentRecordsFromFile(filePath);
  }
  else
  {
    printf("Error: File not found\n");
  }
}

void displayAddStudentMenu()
{
  clearConsole();
  displayBanner();

  char name[30];
  char surname[30];
  char master[30];
  int age;

  // Getting the student's name
  getString("Enter the student's name: ", name, 30, ALPHA_FLAG | SPACE_FLAG);
  // Getting the student's surname
  getString("Enter the student's surname: ", surname, 30, ALPHA_FLAG | SPACE_FLAG);
  // Getting the student's master
  getString("Enter the student's master: ", master, 30, ALPHA_FLAG | NUMBER_FLAG);
  // Getting the student's age
  age = getInt("Enter the student's age: ", 0, 100);

  // Adding the student record to the linked list
  addStudentRecord(name, surname, master, age);

  printf("\nStudent record added\n");
}

static void displayShowStudentMenu()
{
  clearConsole();
  displayBanner();

  int numberOfStudents = getNumberOfStudentRecords();

  printf("Number of students: %d\n\n", numberOfStudents);

  displayStudentRecords();
  waitEnterKey();
}

void displayMainMenu()
{
  bool exit = false;

  while (!exit)
  {
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

    if (selectedOption == LOAD_STUDENTS_FROM_FILE)
    {
      displayLoadFileMenu();
    }
    else if (selectedOption == ADD_STUDENT)
    {
      displayAddStudentMenu();
    }
    else if (selectedOption == EDIT_STUDENT)
    {
      // displayEditStudentMenu();
    }
    else if (selectedOption == REMOVE_STUDENT)
    {
      // displayRemoveStudentMenu();
    }
    else if (selectedOption == DISPLAY_STUDENTS)
    {
      displayShowStudentMenu();
    }
    else if (selectedOption == SAVE_STUDENTS_TO_FILE)
    {
      // displaySaveFileMenu();
    }
    else if (selectedOption == EXIT)
    {
      printf("Thank you for using our system! Bye!\n");
      // Free the linked list
      deleteLinkedListContent();
      exit = true;
      continue;
    }

    freezeConsole(1);
  }
}