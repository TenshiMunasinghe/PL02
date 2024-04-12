#include "flight.h"
#include <stdlib.h>

Flight *initializeFlightInfo()
{
  Flight *pFlight;
  pFlight = (Flight *)malloc(sizeof(Flight));
  if (pFlight == NULL)
    return NULL;

  pFlight->time = (Time *)malloc(sizeof(Time));
  if (pFlight->time == NULL)
  {
    free(pFlight);
    return NULL;
  }

  pFlight->time->hour = 0;
  pFlight->time->minute = 0;
  return pFlight;
};

void freeFlightInfo(Flight *pFlight)
{
  if (pFlight != NULL)
  {
    if (pFlight->time != NULL)
      free(pFlight->time);
    free(pFlight);
  }
};
