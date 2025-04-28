#include "parse.h"

int parseInput(FILE *in, Lines *lines, Rectangles *rects, ColorArr colorArray)
{
  int error = 0; // 0 means no error

  int id;
  char idStr[MAX_ID_DIGIT], type[MAX_TYPE], color[MAX_COLOR_CHAR], pointToken[MAX_TOKEN_SIZE];
  Point p1, p2;

  double a, b, c, d; // for testing

  char ch = fgetc(in);
  if (ch != '#')
    return 0;

  error += getToken(in, idStr, MAX_ID_DIGIT, &isDigit); // parse Id

  id = atoi(idStr);

  error += getToken(in, type, MAX_TYPE, &isAlpha);        // parse type
  error += getToken(in, color, MAX_COLOR_CHAR, &isAlpha); // parse color

  getRestOfLineWithoutSpace(in, pointToken, 256); // get string like "(1.1,1.2)(2.3,3.4)"

  error += parsePoints(pointToken, &p1, &p2);

  if (isColorValid(color, colorArray) == 0)
  {
    printf("Invalid color (%s). Skipping line.\n", color);
    return 1;
  }

  if (strcmp(type, "line") == 0)
  {
    Line *line = addLine(lines, id);
    strcpy(line->color, color);
    computeLineFromPoints(line, p1, p2);
  }
  else if (strcmp(type, "rectangle") == 0)
  {
    Rectangle *rect = addRectangle(rects, id);
    strcpy(rect->color, color);
    computeRectFromPoints(rect, p1, p2);
  }
  else
  {
    error += 1;
  }

  if (error > 0) // if there is error in parsing input
  {
    printf("Error with reading input. Skipping line.\n");
    return 1;
  }

  return 1;
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
  if (sscanf(token, "(%lf,%lf)(%lf,%lf)", &(p1->x), &(p1->y), &(p2->x), &(p2->y)) != 4)
    return 1;
  return 0;
}
