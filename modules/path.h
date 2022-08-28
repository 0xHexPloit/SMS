#ifndef PATH_H
#define PATH_H
#define PATH_MAX 256

struct path
{
  char filePath[PATH_MAX];
};
typedef struct path Path;


Path createPath(const char *filePath);
Path getParentDirectory(const Path* path);
const char* pathToString(const Path* path);

#endif // PATH_H