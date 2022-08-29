#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>

bool checkFileExists(const char *fileName);

bool checkDirectoryExists(const char *directoryName);

bool writeToDisk(const char *fileName, bool (*callback)(const FILE *file));

bool readLinesFromFile(const char *fileName, bool (*callback)(const char *line));


#endif // STORAGE_H