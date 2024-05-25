#include "intersect.h"

int computeLineIntercept(Line *line1, Line *line2)
{

  if ((line1->a / line1->b) == (line2->a / line2->b)) // gradient is equal
  {
    return 0;
  }

  Point intercept;
  intercept.y = (line2->a - line1->a) * line2->c / (line2->a * line1->b - line2->b - line1->a);
  intercept.x = (line1->c - line1->b * intercept.y) / line1->a;

  if (isPointOnLine(intercept, *line1) == 0 || isPointOnLine(intercept, *line2) == 0) // check if intercept is on both line 1 and 2
    return 0;
}

int isPointOnLine(Point p, Line line)
{
  double xMax, xMin;
  if (line.points[0].x > line.points[1].x) // set range of x
  {
    xMax = line.points[0].x;
    xMin = line.points[1].x;
  }
  else
  {
    xMax = line.points[1].x;
    xMin = line.points[0].x;
  }

  if (p.x > xMax || p.x < xMin) // check whether x is in range
    return 0;

  double yMax, yMin;
  if (line.points[0].y > line.points[1].y) // set range of y
  {
    xMax = line.points[0].y;
    xMin = line.points[1].y;
  }
  else
  {
    xMax = line.points[1].y;
    xMin = line.points[0].y;
  }

  if (p.y > yMax || p.y < yMin) // check whether y is in range
    return 0;

  return 1;
}