#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "console.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int getInt(const char *label, int min, int max) {
  fflush(stdin);
  printf("%s", label);
  int choice = 0;
  bool canExit = false;

  while (!canExit)
  {
    if (scanf("%d", &choice) != 1)
    {
      fflush(stdin);
    }

    if (choice >= min && choice <= max)
    {
      canExit = true;
      continue;
    } else {
      printf("Error: Invalid choice");
    }
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

getString(const char *label, char* buffer, int bufferSize) {
  fflush(stdin);
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

void waitEnterKey() {
  fflush(stdin);
  printf("\nPress enter to continue...");
  while (getchar() != '\n') {
    continue;
  }
}