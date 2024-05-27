#include "line.h"
#include "rectangle.h"
#include "utils.h"

#define INTERCEPT_THERESHOLD 0.01

int computeLineIntersect(LineProperties *line1, LineProperties *line2);
int isPointOnLine(Point p, LineProperties line);
double computeRectIntersectArea(Rectangle *r1, Rectangle *r2);
int computeRectTouching(Rectangle *r1, Rectangle *r2);
int computeLineRectIntersect(LineProperties *properties, Rectangle *rect);
int isPointInRect(Point p, Rectangle *rect);
