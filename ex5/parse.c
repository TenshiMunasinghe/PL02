#include "parse.h"

int getToken(FILE *in, char *token, int limit, int (*isValid)(char));
void getRestOfLineWithoutSpace(FILE *in, char token[256], int limit);
int parsePoints(char token[MAX_TOKEN_SIZE], Point *p1, Point *p2);
int isValidIdChar(char ch);
int isValidTypeChar(char ch);
int isValidNameChar(char ch);
int isValidNumChar(char ch);

int parseInput(FILE *in, Lines lines, Rectangles rects)
{
  int error = 1; // 1 means no error
  int id;
  char idStr[MAX_ID_DIGIT], type[MAX_TYPE], name[MAX_NAME], pointToken[256];
  Point p1, p2;

  double a, b, c, d; // for testing

  char ch = fgetc(in);
  if (ch == '#')
    ch = fgetc(in); // skip leading '#'
  else
    return 0;

  error = getToken(in, idStr, MAX_ID_DIGIT, &isValidIdChar); // parse Id
  id = atoi(idStr);

  error = getToken(in, type, MAX_TYPE, &isValidTypeChar); // parse type
  error = getToken(in, name, MAX_NAME, &isValidNameChar); // parse name

  getRestOfLineWithoutSpace(in, pointToken, 256);

  parsePoints(pointToken, &p1, &p2);

  if (error == 0) // if there is error in parsing input
  {
    printf("Error with reading input. Skipping line.\n");
    return 0;
  }

  return 1;
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
    {
      token[ixLit++] = ch;
    }

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

int isValidNumChar(char ch)
{
  return (ch == '.' || ch == '-' || isdigit(ch)) ? 1 : 0;
}

void getRestOfLineWithoutSpace(FILE *in, char token[256], int limit)
{
  char ch = fgetc(in);
  int ix = 0;
  while (ch != '\n' && ch != EOF)
  {
    if (isspace(ch))
    {
      ch = fgetc(in);
      continue;
    }
    if (ix < limit)
    {
      token[ix++] = ch;
      ch = fgetc(in);
    }
  }
  token[ix] = '\0';
}

int parsePoints(char token[MAX_TOKEN_SIZE], Point *p1, Point *p2)
{
  if (sscanf(token, "(%lf,%lf)(%lf,%lf)", &(p1->x), &(p1->y), &(p2->x), &(p2->y)) == 4)
    return 1;
  return 0;
}