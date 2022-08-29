#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "menu.h"
#include "console.h"
#include "student.h"
#include "storage.h"
#include "path.h"

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

  // Getting the student's gender
  char gender;
  char *genderOptions[] = {"Male", "Female"};
  int selectedOption = getOption("Enter the student's gender", genderOptions, sizeof(genderOptions) / sizeof(char *));
  gender = selectedOption == 1 ? 'M' : 'F';

  // Adding the student record to the linked list
  addStudentRecord(name, surname, master, age, gender);

  printf("\nStudent record added\n");
}

static void displayRemoveStudentMenu()
{
  clearConsole();
  displayBanner();

  int id = getInt("Enter the student's ID: ", 1, SHRT_MAX);
  puts("\n");

  if (deleteStudentRecord(id))
  {
    printf("Student record deleted\n");
  }
  else
  {
    printf("Student record not found\n");
  }
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

void displaySaveMenu()
{
  clearConsole();
  displayBanner();

  char buffer[100];
  Path filePath;
  bool canExit = false;

  while (!canExit)
  {
    getString("Enter the path to the file: ", buffer, 100, NO_FLAG);
    filePath = createPath(buffer);
    Path parentDirectory = getParentDirectory(&filePath);

    if (checkDirectoryExists(pathToString(&parentDirectory)))
    {
      canExit = true;
      continue;
    }
    printf("Error: Directory not found\n");
  }

  printf("Writing to file: %s\n", pathToString(&filePath));
  if (writeToDisk(pathToString(&filePath), &saveStudentRecordsToFile))
  {
    int numberOfStudents = getNumberOfStudentRecords();
    printf("%d student record(s) saved to file\n", numberOfStudents);
  }
  else
  {
    printf("Error: Unable to save student records to file\n");
  }

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
      displayRemoveStudentMenu();
    }
    else if (selectedOption == DISPLAY_STUDENTS)
    {
      displayShowStudentMenu();
    }
    else if (selectedOption == SAVE_STUDENTS_TO_FILE)
    {
      displaySaveMenu();
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