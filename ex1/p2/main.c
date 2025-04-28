#include "flight.h"
#include "utils.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseFlightInfo(FILE *fin, Flight *pFlight);
int parseInput(float timeGap, char *departurePoint, char *destinationPoint);

int main()
{
  float timeGap;
  char departurePoint[30], destinationPoint[30];

  printf("Time gap in hours: ");
  if (scanf("%f", &timeGap) != 1)
  {
    printf("Invalid time gap.\n");
    return EXIT_FAILURE;
  }

  printf("Enter your departure point: ");
  if (scanf("%s", departurePoint) != 1)
  {
    printf("Invalid departure point.\n");
    return EXIT_FAILURE;
  }

  printf("Enter your destination point: ");
  if (scanf("%s", destinationPoint) != 1)
  {
    printf("Invalid destination point.\n");
    return EXIT_FAILURE;
  }
  parseInput(timeGap, departurePoint, destinationPoint);

  return EXIT_SUCCESS;
}

int parseFlightInfo(FILE *fin, Flight *pFlight)
{
  if (fin == NULL || pFlight == NULL)
    return 0;

  return fscanf(fin, "%s %s %d:%d", pFlight->id, pFlight->location,
                &pFlight->time->hour, &pFlight->time->minute);
}

int parseInput(float timeGap, char *departurePoint, char *destinationPoint)
{
  FILE *fArrival, *fDeparture, *fout;
  Flight *arrivalInfo = initializeFlightInfo();
  Flight *departureInfo = initializeFlightInfo();

  fArrival = fopen("arrival.txt", "r");
  fDeparture = fopen("departure.txt", "r");
  fout = fopen("output.txt", "wt");

  if (fArrival == NULL || fDeparture == NULL)
  {
    printf("Failed to read file.\n");
    return 0;
  }
  printf("Available connected flights:\n");

  while (parseFlightInfo(fArrival, arrivalInfo) == 4)
  {
    if (strcmp(arrivalInfo->location, departurePoint) != 0)
      continue;

    if (!isValidTime(*arrivalInfo->time))
    {
      printf("Invalid time for flight %s. Ignoring this flight...\n",
             arrivalInfo->id);
      continue;
    }

    while (parseFlightInfo(fDeparture, departureInfo) == 4)
    {
      if (strcmp(departureInfo->location, destinationPoint) != 0)
        continue;

      if (timeDifference(*departureInfo->time, *arrivalInfo->time) > timeGap)
      {
        char outputStr[50];

        snprintf(outputStr, sizeof(outputStr), "%s %s %d:%d %s %s %d:%d\n", arrivalInfo->id, arrivalInfo->location,
                 arrivalInfo->time->hour, arrivalInfo->time->minute, departureInfo->id, departureInfo->location,
                 departureInfo->time->hour, departureInfo->time->minute);

        printf("%s", outputStr);
        fprintf(fout, "%s", outputStr);
      }
    }
    rewind(fDeparture);
  };

  fclose(fArrival);
  fclose(fDeparture);
  freeFlightInfo(arrivalInfo);
  freeFlightInfo(departureInfo);

  return 1;
};
