#include <stdlib.h>

int strToInt(char *str, int *n)
{
  char *endptr;
  *n = strtol(str, &endptr, 10);

  if (*endptr != '\0')
  {
    printf("Conversion error\n");
    return 0;
  }

  return 1;
};

int isNum(const char *str)
{
  if (str == NULL || *str == '\0')
  {
    return 0;
  }

  // Check for digits
  while (*str != '\0')
  {
    if (isdigit(*str))
    {
      str++;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}