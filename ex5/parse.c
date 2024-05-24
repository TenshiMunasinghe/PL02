#include "parse.h"

int isValidIdChar(char ch);
int isValidTypeChar(char ch);
int isValidNameChar(char ch);
int getToken(FILE *in, char *token, int limit, int (*isValid)(char));

int parseInput(FILE *in, Lines lines, Rectangles rects)
{
  int error = 1; // 1 means no error
  int id;
  char idStr[MAX_ID_DIGIT], type[MAX_TYPE], name[MAX_NAME];
  Point p1, p2;

  error = getToken(in, idStr, MAX_ID_DIGIT, &isValidIdChar); // parse Id
  id = atoi(idStr);

  error = getToken(in, type, MAX_TYPE, &isValidTypeChar); // parse type
  error = getToken(in, name, MAX_NAME, &isValidNameChar); // parse name

  if (error == 0) // if there is error in parsing input
  {
    printf("Error with reading input. Skipping line.\n");
    return 0;
  }
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
      return 0;

    if (ixLit < limit)
      token[ixLit++] = ch;

    ch = fgetc(in);
  }
  token[ixLit] = '\0';

  return 1;
}

int isValidIdChar(char ch)
{
  return isdigit(ch);
}

int isValidTypeChar(char ch)
{
  return isalpha(ch);
}

int isValidNameChar(char ch)
{
  return (isalpha(ch) || isdigit(ch)) ? 1 : 0;
}
