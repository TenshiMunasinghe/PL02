#include "parse.h"

int getToken(FILE *in, char *token, int limit, int (*isValid)(char));
void parsePoints(char input[MAX_TOKEN_SIZE], Point *p);
int isValidIdChar(char ch);
int isValidTypeChar(char ch);
int isValidNameChar(char ch);
void trim(char *str);

int parseInput(FILE *in, Lines lines, Rectangles rects)
{
  int error = 1; // 1 means no error
  int id;
  char idStr[MAX_ID_DIGIT], type[MAX_TYPE], name[MAX_NAME], p1Token[MAX_TOKEN_SIZE], p2Token[MAX_TOKEN_SIZE];
  Point p1, p2;

  error = getToken(in, idStr, MAX_ID_DIGIT, &isValidIdChar); // parse Id
  id = atoi(idStr);

  error = getToken(in, type, MAX_TYPE, &isValidTypeChar); // parse type
  error = getToken(in, name, MAX_NAME, &isValidNameChar); // parse name

  // error = getToken(in, p1Token, MAX_TOKEN_SIZE, )

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

void parsePoints(char input[MAX_TOKEN_SIZE], Point *p)
{
  char buffer[MAX_TOKEN_SIZE];
  strcpy(buffer, input);

  // Trim leading and trailing spaces
  trim(buffer);

  // Check if the string starts with '(' and ends with ')'
  if (buffer[0] == '(' && buffer[strlen(buffer) - 1] == ')')
  {
    buffer[strlen(buffer) - 1] = '\0';           // Remove the trailing ')'
    memmove(buffer, buffer + 1, strlen(buffer)); // Remove the leading '('

    // Find the comma
    char *comma = strchr(buffer, ',');
    if (comma)
    {
      *comma = '\0'; // Split the string into two parts
      comma++;
      // Trim spaces around the numbers
      trim(buffer);
      trim(comma);
      // Convert strings to floats
      p->x = strtof(buffer, NULL);
      p->y = strtof(comma, NULL);
    }
  }
}

void trim(char *str)
{
  char *end;
  // Trim leading spaces
  while (isspace((unsigned char)*str))
    str++;
  // Trim trailing spaces
  if (*str == 0)
    return;
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;
  *(end + 1) = 0;
}