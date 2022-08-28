#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

#define NO_FLAG 0
#define ALPHA_FLAG 1
#define SPACE_FLAG 2
#define NUMBER_FLAG 4

int getOption(const char *label, const char **options, int numberOptions);

static bool checkString(const char *string, int flags);

void getString(const char *label, char* buffer, int bufferSize, int flags);

int getInt(const char *label, int min, int max);

void freezeConsole(int seconds);

void clearConsole();

void waitEnterKey();

#endif // CONSOLE_H