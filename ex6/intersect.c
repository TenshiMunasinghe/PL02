#include "intersect.h"

int computeLineIntersect(Point l1[2], Point l2[2])
{
  double a1 = l1[1].y - l1[0].y;
  double b1 = l1[0].x - l1[1].x;
  double c1 = a1 * l1[0].x + b1 * l1[0].y;

  double a2 = l2[1].y - l2[0].y;
  double b2 = l2[0].x - l2[1].x;
  double c2 = a2 * l2[0].x + b2 * l2[0].y;

  double determinant = a1 * b2 - a2 * b1;

  if (determinant == 0)
  {
    // The lines are parallel
    return 0;
  }
  else
  {
    double x = (b2 * c1 - b1 * c2) / determinant;
    double y = (a1 * c2 - a2 * c1) / determinant;

    // Check if the intersection point (x, y) lies on both line segments
    if (x >= min(l1[0].x, l1[1].x) && x <= max(l1[0].x, l1[1].x) &&
        y >= min(l1[0].y, l1[1].y) && y <= max(l1[0].y, l1[1].y) &&
        x >= min(l2[0].x, l2[1].x) && x <= max(l2[0].x, l2[1].x) &&
        y >= min(l2[0].y, l2[1].y) && y <= max(l2[0].y, l2[1].y))
    {
      return 1;
    }
  }
  return 0;
}

int computeLineRectIntersect(Line *line, Rectangle *rect)
{ // check if a point of line segment is inside rectangle
  if (isPointInRect(line->points[0], rect) == 1 || isPointInRect(line->points[1], rect) == 1)
  {
    return 1;
  }
  // check if the line segment intercept with edges of the rectangle
  for (int i = 0; i < 4; i++)
  { // rectEdgePoints {points[0], points[1]} represent top edge of rectangle as points start from top-left and go clock-wise
    // like wise, {points[1], points[2]} represent right edge and so on...
    Point rectEdgePoints[2] = {rect->points[i], rect->points[(i % 4)]};
    if (computeLineIntersect(line->points, rectEdgePoints) == 1)
      return 1;
  }

  return 0;
}

int isPointInRect(Point p, Rectangle *rect)
{
  // check if p is within the ranges of x and y
  if (p.x > rect->x.min && p.x < rect->x.max && p.y > rect->y.min && p.y < rect->y.max)
  {
    return 1;
  }
  return 0;
}

double computeRectIntersectArea(Rectangle *r1, Rectangle *r2)
{
  return max(0, min(r1->x.max, r2->x.max) - max(r1->x.min, r2->x.min)) * max(0, min(r1->y.max, r2->y.max) - max(r1->y.min, r2->y.min));
}

int computeRectTouching(Rectangle *r1, Rectangle *r2)
{
  if (min(r1->x.max, r2->x.max) - max(r1->x.min, r2->x.min) + min(r1->y.max, r2->y.max) - max(r1->y.min, r2->y.min) > 0)
    return 1;
  return 0;
}