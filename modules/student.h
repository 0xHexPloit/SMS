#ifndef STUDENT_H
#define STUDENT_H

typedef struct
{
  char name[30];
  char surname[30];
  char master[30];
  int age;
  int id;
} Student;

typedef struct linkedList
{
  Student student;
  struct linkedList *next;
} StudentLinkedList;

static StudentLinkedList *getTail(StudentLinkedList *head);

int addStudentRecord(char *name, char *surname, char *master, int age);

void deleteLinkedListContent();

void loadStudentRecordsFromFile(const char *filePath);

int getNumberOfStudentRecords();

static void displayStudent(Student student);

void displayStudentRecords();

#endif // STUDENT_H