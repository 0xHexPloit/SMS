#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 20
#define MAX_SURNAME_LENGTH 20
#define MAX_MASTER_LENGTH 20

typedef struct
{
  char name[MAX_NAME_LENGTH];
  char surname[MAX_SURNAME_LENGTH];
  char master[MAX_MASTER_LENGTH];
  int age;
  int id;
  char gender;


} Student;


typedef struct linkedList
{
  Student student;
  struct linkedList *next;
} StudentLinkedList;

bool askUserForName(char *name, int length);
bool askUserForSurname(char *surname, int length);
bool askUserForMaster(char *master, int length);
bool askUserForAge(int *age);
bool askUserForGender(char *gender);

bool checkName(const char *name);

bool checkSurname(const char *surname);

bool checkMaster(const char *master);

bool checkAge(int age);

bool checkGender(char gender);

bool addStudentRecord(char *name, char *surname, char *master, int age, char gender);

bool deleteStudentRecord(int id);

void deleteLinkedListContent();

bool createStudentFromString(const char *line);

int getNumberOfStudentRecords();

static void displayStudent(Student student);

void displayStudentRecords();

bool saveStudentRecordsToFile(const FILE *file);

Student* getStudentRecord(int id);

void setStudentName(Student* student, const char *name);

void setStudentSurname(Student* student, const char *surname);

void setStudentMaster(Student* student, const char *master);

void setStudentAge(Student* student, int age);

void setStudentGender(Student* student, char gender);


#endif // STUDENT_H