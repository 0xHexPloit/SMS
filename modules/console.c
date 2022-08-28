#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "console.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int getInt(const char *label, int min, int max)
{
  char buffer[32];
  int choice = 0;
  bool canExit = false;

  while (!canExit)
  {
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    choice = atoi(buffer);

    if (choice == 0)
    {
      fflush(stdin);
    }
    else if (choice >= min && choice <= max)
    {
      canExit = true;
      continue;
    }
    printf("Invalid input. Please enter a number between %d and %d\n", min, max);
  }
  return choice;
}

int getOption(const char *label, const char **options, int numberOptions)
{
  fflush(stdin);
  // Displaying the label if not null
  if (label != NULL)
  {
    printf("%s", label);
  }

  // Displaying the options
  for (int i = 0; i < numberOptions; i++)
  {
    printf("[%d] >> %s\n", i + 1, options[i]);
  }
  puts("\n");

  // Getting the user input
  return getInt("Enter your choice: ", 1, numberOptions);
}

static bool checkString(const char *string, int flags)
{
  for (int i = 0; i < strlen(string); i++)
  {
    if (flags & ALPHA_FLAG)
    {
      if (isalpha(string[i]) != 0)
        continue;
    }
    if (flags & SPACE_FLAG)
    {
      if (isspace(string[i]) != 0)
        continue;
    }

    if (flags & NUMBER_FLAG)
    {
      if (isdigit(string[i]) != 0)
        continue;
    }
    return false;
  }
  return true;
}

void getString(const char *label, char *buffer, int bufferSize, int flags)
{
  while (true)
  {
    printf("%s", label);
    fgets(buffer, bufferSize, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    if (flags == NO_FLAG)
      return;

    if (checkString(buffer, flags))
      return;

    printf("Invalid input. Please enter a valid string\n");
  }
}

void freezeConsole(int seconds)
{
  sleep(seconds);
}

void clearConsole()
{
  system("clear");
}

void waitEnterKey()
{
  fflush(stdin);
  printf("\nPress enter to continue...");
  while (getchar() != '\n')
  {
    continue;
  }
}