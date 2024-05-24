#pragma once

#include <stdio.h>
#include "point.h"

#define RECT_POINT_NUM 4

typedef Point Rectangle[RECT_POINT_NUM];

typedef struct
{
  int size;
  Rectangle *all;
} Rectangles;