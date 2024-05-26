#include "line.h"
#include "rectangle.h"
#include "minmax.h"

#define INTERCEPT_THERESHOLD 0.01

int computeLineIntercept(Line *line1, Line *line2);
int isPointOnLine(Point p, Line line);
double computeRectIntersectArea(Rectangle *r1, Rectangle *r2);
