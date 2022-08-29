#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

int getOption(const char *label, const char **options, int numberOptions);

void getString(const char *label, char* buffer, int bufferSize);

int getInt(const char *label);

void freezeConsole(int seconds);

void clearConsole();

void waitEnterKey();

#endif // CONSOLE_H