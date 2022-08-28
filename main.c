#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "modules/menu.h"
#include "modules/storage.h"
#include "modules/student.h"

int terminationHandler(int signum)
{
  printf("\nFreeing memory\n");
  deleteLinkedListContent();
  exit(0);
}

int main()
{
  struct sigaction sa;
  sa.sa_handler = terminationHandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);

  displayMainMenu();
  return EXIT_SUCCESS;
}