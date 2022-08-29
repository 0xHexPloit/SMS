#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

bool checkString(const char *string, int flags)
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