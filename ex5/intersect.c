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

  if (isPointOnLine(intercept, *line1) == 0) // check if intercept is on a line
    return 0;
}

int isPointOnLine(Point p, Line line)
{

  if (p.x > min(line.points[0].x, line.points[1].x) || p.x < max(line.points[0].x, line.points[1].x)) // check whether x is in range
    return 0;

  if (p.y > min(line.points[0].y, line.points[1].y) || p.y < max(line.points[0].y, line.points[1].y)) // check whether x is in range
    return 0;

  return 1;
};

double computeRectIntersectArea(Rectangle *r1, Rectangle *r2)
{
  return max(0, min(r1->x.max, r2->x.max) - max(r1->x.min, r2->x.min)) * max(0, min(r1->y.max, r2->y.max) - max(r1->y.min, r2->y.min));
}