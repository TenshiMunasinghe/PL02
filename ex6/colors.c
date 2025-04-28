#include "colors.h"

void parseColors(ColorArr colorArray)
{
  int error;
  FILE *in = fopen("colors.txt", "rt");
  char colorToken[MAX_COLOR_CHAR];

  for (int i = 0; i < MAX_COLOR_NUM; i++)
  {
    char prev[MAX_COLOR_CHAR];
    strcpy(prev, colorToken);
    error += getToken(in, colorToken, MAX_COLOR_CHAR, &isAlpha);

    if (strcmp(prev, colorToken) == 0) // Insert an empty string when last element is fetched for the second time
    {
      strcpy(colorArray[i], "\0");
      continue;
    }

    strcpy(colorArray[i], colorToken);
  }
}

int isColorValid(char *color, ColorArr arr)
{
  for (int i = 0; i < MAX_COLOR_NUM; i++)
  {
    if (strlen(arr[i]) == 0)
    {
      break; // Exit loop if an empty string is encountered
    }
    if (strcmp(color, arr[i]) == 0)
      return 1;
  }
  return 0;
}