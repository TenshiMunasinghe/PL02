#include "utils.h"

double min(double a, double b)
{
  return a > b ? b : a;
}

double max(double a, double b)
{
  return a > b ? a : b;
}

int compareDouble(double a, double b)
{
  if (fabs(a - b) < DOUBLE_COMPSRISON_THRESHOLD)
    return 1;
  return 0;
}

int getToken(FILE *in, char *token, int limit, int (*isValid)(char))
{
  char ch = fgetc(in);

  int ixLit = 0;

  // Skip leading spaces
  while (isspace(ch))
    ch = fgetc(in);
  if (ch == EOF)
    return EOF;

  while (!isspace(ch) && ch != EOF)
  {
    if (!isValid(ch))
      return 1;

    if (ixLit < limit)
    {
      token[ixLit++] = ch;
    }

    ch = fgetc(in);
  }
  token[ixLit] = '\0';

  return 0;
}

int isDigit(char ch)
{
  return isdigit(ch);
}

int isAlpha(char ch)
{
  return isalpha(ch);
}
