#include "line.h"

int computeLineFromPoints(Line *line, Point p1, Point p2)
{
  if (isPointEqual(p1, p2) == 1)
  {
    printf("Same points detected for line construction, ignoring input.\n");
    return 0;
  }

  if (p1.x == p2.x) // line is in form x=c
  {
    line->a = 1;
    line->b = 0;
    line->c = p1.x;
  }
  else if (p1.y == p2.y) // line is in form y=c
  {
    line->a = 0;
    line->b = 1;
    line->c = p1.y;
  }
  else
  { // line is in form ax+by=c (y=mx+c <=> y-mx=c)
    double gradient = (p1.y - p2.y) / (p1.x - p2.x);
    double intercept = p1.y - (gradient * p1.x);

    line->b = 1;
    line->a = gradient * -1;
    line->c = intercept;
  }

  return 1;
}