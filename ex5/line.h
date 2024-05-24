#pragma once

#include "point.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  double a;
  double b;
  double c;
} Line; // In form of ax+by=c

typedef struct
{
  int size;
  Line *all;
} Lines;