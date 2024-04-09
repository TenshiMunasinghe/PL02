#include <math.h>
#include "point.h"

#define epsilon 0.01

int isFloatEqual(float a, float b)
{
  if (fabs(a - b) <= epsilon)
    return 1;
  return 0;
};

int isPointEqual(Point p1, Point p2)
{
  if (isFloatEqual(p1.x, p2.x) && isFloatEqual(p1.y, p2.y))
    return 1;
  return 0;
};