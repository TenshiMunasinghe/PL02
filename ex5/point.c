#include "point.h"

int isPointEqual(Point p1, Point p2)
{
  if ((p1.x == p2.x) && (p1.y == p2.y))
    return 1;
  else
    return 0;
}

void setPoint(Point *p, double x, double y)
{

  p->x = x;
  p->y = y;
}

void printPoint(Point p)
{
  printf("%lf %lf\n", p.x, p.y);
}