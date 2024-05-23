#pragma once

#include <stdio.h>
#include "point.h"

typedef Point Rectangle[4];

typedef struct
{
  int size;
  Rectangle *all;
} Rectangles;