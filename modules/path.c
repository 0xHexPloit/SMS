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
  strncpy(path.filePath, filePath, PATH_MAX);
  return path;
}

Path getParentDirectory(const Path *path)
{
  Path parentDirectory;
  for (int i = strlen(path->filePath) - 1; i >= 0; i--)
  {
    if (path->filePath[i] == SEP[0])
    {
      char buffer[PATH_MAX];
      strncpy(buffer, path->filePath, i + 1);
      buffer[i + 1] = '\0';
      strncpy(parentDirectory.filePath, buffer, PATH_MAX);
      break;
    }
  }
  return parentDirectory;
}

const char *pathToString(const Path *path)
{
  return path->filePath;
}
