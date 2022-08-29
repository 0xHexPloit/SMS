#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int getInt(const char *label)
{
  char buffer[32];
  int choice = 0;

  while (true)
  {
    printf("%s", label);
    fgets(buffer, sizeof(buffer), stdin);
    char* endPtr;
    choice = (int)strtol(buffer, &endPtr, 10);

    if (endPtr == buffer || *endPtr != '\n')
    {
      printf("Invalid input.\n");
      continue;
    }
    return choice;
  }
}

int getOption(const char *label, const char **options, int numberOptions)
{
  fflush(stdin);
  // Displaying the label if not null
  if (label != NULL)
  {
    printf("%s\n", label);
  }

  // Displaying the options
  for (int i = 0; i < numberOptions; i++)
  {
    printf("[%d] >> %s\n", i + 1, options[i]);
  }
  puts("\n");

  // Getting the user input
  while (true)
  {
    int choice = getInt("Enter your choice: ");
    if (choice > 0 && choice <= numberOptions)
    {
      return choice;
    }
    else
    {
      printf("Invalid choice\n");
    }
  }
}

void getString(const char *label, char *buffer, int bufferSize)
{
  printf("%s", label);
  fgets(buffer, bufferSize, stdin);
  buffer[strlen(buffer) - 1] = '\0';
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