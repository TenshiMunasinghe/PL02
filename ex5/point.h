#pragma once

#include <stdio.h>

typedef struct
{
  double x;
  double y;
} Point;

int isPointEqual(Point p1, Point p2);
void setPoint(Point *p, double x, double y);
void printPoint(Point p);