#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

StudentLinkedList *head = NULL;
StudentLinkedList *tail = NULL;
int numberOfStudents = 0;

bool addStudentRecord(char *name, char *surname, char *master, int age)
{
  StudentLinkedList *newStudent = (StudentLinkedList *)malloc(sizeof(StudentLinkedList));
  if (newStudent == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return false;
  }
  newStudent->student.id = tail == NULL ? 1 : tail->student.id + 1;
  strncpy(newStudent->student.name, name, 30);
  strncpy(newStudent->student.surname, surname, 30);
  strncpy(newStudent->student.master, master, 30);
  newStudent->student.age = age;
  newStudent->next = NULL;

  if (head == NULL)
  {
    head = newStudent;
    tail = newStudent;
  }
  else
  {
    tail->next = newStudent;
    tail = newStudent;
  }
  numberOfStudents++;
  return true;
}

bool deleteStudentRecord(int id)
{
  StudentLinkedList *current = head;
  StudentLinkedList *previous = NULL;

  while (current != NULL)
  {
    // Iterate through the linked list and find the student with the given id
    if (current->student.id != id)
    {
      previous = current;
      current = current->next;
      continue;
    }

    // Dealing the case where the student is the first one in the linked list
    if (previous == NULL)
    {
      head = current->next;
    }
    else
    {
      previous->next = current->next;
    }
    free(current);
    numberOfStudents--;
    return true;
  }

  return false;
}

void deleteLinkedListContent()
{
  StudentLinkedList *current = head;
  while (current != NULL)
  {
    StudentLinkedList *next = current->next;
    free(current);
    current = next;
  }
}

void loadStudentRecordsFromFile(const char *filePath)
{
  printf("Loading students from file %s\n", filePath);
}

int getNumberOfStudentRecords()
{
  return numberOfStudents;
}

static void displayStudent(Student student)
{
  puts("Student {");
  printf("  id: %d\n", student.id);
  printf("  name: %s\n", student.name);
  printf("  surname: %s\n", student.surname);
  printf("  master: %s\n", student.master);
  printf("  age: %d\n", student.age);
  puts("}\n");
}

void displayStudentRecords()
{
  StudentLinkedList *current = head;
  while (current != NULL)
  {
    displayStudent(current->student);
    current = current->next;
  }
}

bool saveStudentRecordsToFile(const FILE *file)
{
  StudentLinkedList *current = head;
  while (current != NULL)
  {
    int output = fprintf(file, "%d %s %s %s %d\n", current->student.id, current->student.name, current->student.surname, current->student.master, current->student.age);
    if (output < 0)
    {
      printf("Error: Writing to file failed\n");
      return false;
    }
    current = current->next;
  }
  return true;
}
