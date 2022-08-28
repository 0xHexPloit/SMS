#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#ifdef _win32
#define SEP "\\"
#else
#define SEP "/"
#endif


int createNewFileInDisk()
{
  char filePath[100] = "";
  char fileName[20] = "";

  // Getting the name of the file
  printf("Enter a name for the database that you want to create: ");
  scanf("%20s", fileName);
  printf("\n");

  // Getting the location where the file will be created
  printf("Enter the location where the file will be created: ");
  scanf("%100s", filePath);
  printf("\n");

  // Tempting to create the file
  if (filePath[strlen(filePath) - 1] != SEP[0])
  {
    strncat(filePath, SEP, strlen(SEP));
  }
  strncat(filePath, fileName, strlen(fileName));

  printf("Creating new database file in %s\n", filePath);

  FILE *file = fopen(filePath, "w");
  if (file == NULL)
  {
    printf("Error creating file\n");
    return -1;
  }
  fclose(file);
  return 0;
}

bool checkFileExists(const char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (file == NULL)
  {
    return false;
  }
  fclose(file);
  return true;
}