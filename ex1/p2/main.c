#include "flight.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHT_COUNT 50
#define FLIGHT_ID_LENGTH 6
#define MAX_NAME_LENGTH 30
#define INPUT_DELIMETER " "
#define TIME_DELIMETER ":"

int isValidTime(Time time) {
  if (time.hour >= 0 && time.minute >= 0 && time.minute < 60)
    return 1;
  return 0;
}

int parseFlightInfo(FILE *fin, Flight *pFlight) {
  pFlight->time = (Time *)malloc(sizeof(Time));
  return fscanf(fin, "%s %s %d:%d", pFlight->id, pFlight->location,
                &(pFlight->time->hour), &(pFlight->time->minute));
}

int parseInput(int timeGap, char *departurePoint, char *destinationPoint) {
  FILE *fArrival, *fDeparture;
  Flight arrivalInfo, departureInfo;

  fArrival = fopen("arrival.txt", "r");
  fDeparture = fopen(("departure.txt"), "r");
  printf("s\n");
  // segmentation error here.
  while (parseFlightInfo(fArrival, &arrivalInfo) != 4) {
    printf("%s %s %d:%d\n", arrivalInfo.id, arrivalInfo.location,
           arrivalInfo.time->hour, arrivalInfo.time->minute);
    if (strcmp(arrivalInfo.location, departurePoint) != 0) {
      continue;
    }
    if (!isValidTime(*arrivalInfo.time)) {
      printf("Invalid time for flight %s. Ignoring this flight...\n",
             arrivalInfo.id);
      continue;
    }
    // while (parseFlightInfo(fin, &departureInfo) == 4) {
    // }
    // rewind(fDeparture);
  };
  return 1;
};

int main() {
  int timeGap;
  char departurePoint[30], destinationPoint[30];

  printf("Time gap in hours: ");
  if (scanf("%d", &timeGap) != 1) {
    printf("Invalid time gap.\n");
    return EXIT_FAILURE;
  }

  printf("Enter your departure point: ");
  if (scanf("%s", departurePoint) != 1) {
    printf("Invalid departure point.\n");
    return EXIT_FAILURE;
  }

  printf("Enter your destination point: ");
  if (scanf("%s", destinationPoint) != 1) {
    printf("Invalid destination point.\n");
    return EXIT_FAILURE;
  }
  parseInput(timeGap, departurePoint, destinationPoint);

  return EXIT_SUCCESS;
}
