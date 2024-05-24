#include "parse.h"

int getToken(FILE *in, char *token, int limit, int (*isValid)(char));
int parsePoints(char input[MAX_TOKEN_SIZE], double x, double y);
int isValidIdChar(char ch);
int isValidTypeChar(char ch);
int isValidNameChar(char ch);
int isValidNumChar(char ch);

// Just use sscans I guess?

int parseInput(FILE *in, Lines lines, Rectangles rects)
{
  int error = 1; // 1 means no error
  int id;
  char idStr[MAX_ID_DIGIT], type[MAX_TYPE], name[MAX_NAME], p1Token[MAX_TOKEN_SIZE], p2Token[MAX_TOKEN_SIZE];
  Point p1, p2;

  double a, b, c, d; // for testing

  error = getToken(in, idStr, MAX_ID_DIGIT, &isValidIdChar); // parse Id
  id = atoi(idStr);

  error = getToken(in, type, MAX_TYPE, &isValidTypeChar); // parse type
  error = getToken(in, name, MAX_NAME, &isValidNameChar); // parse name

  // get tokens for coordinate points
  error = getToken(in, p1Token, MAX_TOKEN_SIZE, &isValidNumChar);
  error = getToken(in, p2Token, MAX_TOKEN_SIZE, &isValidNumChar);
  printf("%s %s %s\n", idStr, type, name);

  // parse the tokens
  error = parsePoints(p1Token, a, b);
  error = parsePoints(p2Token, c, d);

  printf("(%lf, %lf) (%lf, %lf)\n", a, b, c, d);

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
  if (ch == '#')
    ch = fgetc(in); // skip leading '#'

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

int parsePoints(char input[MAX_TOKEN_SIZE], double x, double y)
{
  char buffer[MAX_TOKEN_SIZE];
  strcpy(buffer, input);

  // Check if the string starts with '(' and ends with ')'
  if (buffer[0] != '(' || buffer[strlen(buffer) - 1] != ')')
  {
    printf("%s\n", input);
    printf("Invalid format for coordinates\n");
    return 0;
  }

  buffer[strlen(buffer) - 1] = '\0';           // Remove the trailing ')'
  memmove(buffer, buffer + 1, strlen(buffer)); // Remove the leading '('

  // Find the comma
  char *comma = strchr(buffer, ',');
  if (!comma)
    return 0;

  *comma = '\0'; // Split the string into two parts
  comma++;

  // Convert strings to floats
  char *endptr;
  x = strtof(buffer, &endptr);
  if (*endptr != '\0')
  {
    printf("Invalid format for coordinates\n");
    return 0; // Invalid float in the first part
  }
  y = strtof(comma, &endptr);
  if (*endptr != '\0')
  {
    printf("Invalid format for coordinates\n");
    return 0; // Invalid float in the second part
  }
  return 1;
}