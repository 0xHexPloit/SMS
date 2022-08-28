#ifndef CONSOLE_H
#define CONSOLE_H

int getOption(const char *label, const char **options, int numberOptions);

getString(const char *label, char* buffer, int bufferSize);

int getInt(const char *label, int min, int max);

void freezeConsole(int seconds);

void clearConsole();

void waitEnterKey();

#endif // CONSOLE_H