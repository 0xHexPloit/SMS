#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "storage.h"

bool checkFileExists(const char *fileName)
{
  FILE *file = fopen(fileName, "r");

  if (file == NULL)
  {
    return false;
  }
  fclose(file);
  return true;
}

bool checkDirectoryExists(const char *directoryName)
{
  struct stat sb;

  if (stat(directoryName, &sb) == 0 && S_ISDIR(sb.st_mode))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool writeToDisk(const char *fileName, bool *callback(const FILE *file)) {
  FILE *file = fopen(fileName, "w");
  if (file == NULL)
  {
    printf("An error occured while opening the file\n");
    return false;
  }
  bool result = callback(file);
  fclose(file);
  return result;
}