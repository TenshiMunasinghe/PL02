#include "utils.h"

double min(double a, double b)
{
  return a > b ? b : a;
}

double max(double a, double b)
{
  return a > b ? a : b;
}

int compareDouble(double a, double b)
{
  if (fabs(a - b) < DOUBLE_COMPSRISON_THRESHOLD)
    return 1;
  return 0;
}