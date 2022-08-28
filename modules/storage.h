#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>

bool checkFileExists(const char *fileName);

bool checkDirectoryExists(const char *directoryName);

bool writeToDisk(const char *fileName, bool *callback(const FILE *file));

#endif // STORAGE_H