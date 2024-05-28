#include "line.h"
#include "rectangle.h"
#include "utils.h"

#define INTERCEPT_THERESHOLD 0.01

int computeLineIntersect(Point l1[2], Point l2[2]);
double computeRectIntersectArea(Rectangle *r1, Rectangle *r2);
int computeRectTouching(Rectangle *r1, Rectangle *r2);
int computeLineRectIntersect(Line *line, Rectangle *rect);
int isPointInRect(Point p, Rectangle *rect);
