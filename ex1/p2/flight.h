#pragma once

#include "time.h"

typedef struct
{
  char id[10];
  char location[30];
  Time *time;
} Flight;

Flight *initializeFlightInfo();
void freeFlightInfo(Flight *pFlight);
