#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

StudentLinkedList *head = NULL;
StudentLinkedList *tail = NULL;
int numberOfStudents = 0;

int addStudentRecord(char *name, char *surname, char *master, int age)
{
  StudentLinkedList *newStudent = (StudentLinkedList *)malloc(sizeof(StudentLinkedList));
  if (newStudent == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return -1;
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