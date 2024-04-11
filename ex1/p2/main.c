#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
#include "util.h"

#define MAX_FLIGHT_COUNT 50
#define FLIGHT_ID_LENGTH 6
#define MAX_NAME_LENGTH 30
#define INPUT_DELIMETER " "
#define TIME_DELIMETER ":"

int parseSingleLine(char *line, char *flightInfo)
{
  char *id, *location;
  Time time;

  char *copiedLine = copyLine(line);
  copiedLine = strtok(copiedLine, INPUT_DELIMETER);

  id[0] = '\0'; // Initialize  buffer
  location[0] = '\0';

  if (copiedLine == NULL || strlen(copiedLine) >= FLIGHT_ID_LENGTH)
  {
    printf("Failed to parse flight ID.\n");
    return 0;
  }
  strcpy(id, copiedLine);
  copiedLine = strtok(NULL, INPUT_DELIMETER);

  if (copiedLine == NULL || strlen(copiedLine) >= MAX_NAME_LENGTH)
  {
    printf("Failed to parse location name.\n");
    return 0;
  }
  strcpy(location, copiedLine);

  copiedLine = strtok(NULL, TIME_DELIMETER);

  // if (isNum(copiedLine))
}

int parseAllLines(FILE *fin, Flight *pList)
{
  char line[MAX_FLIGHT_COUNT + 1];
  int count = 0;

  while (fgets(line, sizeof(line), fin))
  {
    count++;
    if (!parseLine(line, pList))
    {
      printf("Error while parsing line %d\n", count);
      exit(EXIT_FAILURE);
    }
  };
}

int main()
{
  FILE *fin, *fout;

  return EXIT_SUCCESS;
}