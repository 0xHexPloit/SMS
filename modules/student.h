#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>
typedef struct
{
  char name[30];
  char surname[30];
  char master[30];
  int age;
  int id;
  char gender;
} Student;

typedef struct linkedList
{
  Student student;
  struct linkedList *next;
} StudentLinkedList;

static StudentLinkedList *getTail(StudentLinkedList *head);

bool addStudentRecord(char *name, char *surname, char *master, int age);

bool deleteStudentRecord(int id);

void deleteLinkedListContent();

void loadStudentRecordsFromFile(const char *filePath);

int getNumberOfStudentRecords();

static void displayStudent(Student student);

void displayStudentRecords();

bool saveStudentRecordsToFile(const FILE *file);

#endif // STUDENT_H