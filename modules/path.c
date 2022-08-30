#include <string.h>
#include "path.h"

#ifdef _win32
#define SEP "\\"
#else
#define SEP "/"
#endif

Path createPath(const char *filePath)
{
  Path path;
  strncpy(path.filePath, filePath, MAX_FILE_PATH);
  return path;
}

Path getParentDirectory(const Path *path)
{
  for (int i = (int)strlen(path->filePath) - 1; i >= 0; i--)
  {
    if (path->filePath[i] == SEP[0])
    {
      Path parentDirectory;
      char buffer[MAX_FILE_PATH];
      strncpy(buffer, path->filePath, i + 1);
      buffer[i + 1] = '\0';
      strncpy(parentDirectory.filePath, buffer, MAX_FILE_PATH);
      return parentDirectory;
    }
  }
  Path parentDirectory = {.filePath = ""};
  return parentDirectory;
}

const char *pathToString(const Path *path)
{
  return path->filePath;
}
