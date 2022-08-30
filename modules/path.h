#ifndef PATH_H
#define PATH_H

#define MAX_FILE_PATH 256

struct path
{
  char filePath[MAX_FILE_PATH];
};
typedef struct path Path;




Path createPath(const char *filePath);
Path getParentDirectory(const Path* path);
const char* pathToString(const Path* path);

#endif // PATH_H