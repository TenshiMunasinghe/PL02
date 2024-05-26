#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "shape.h"
#include "minmax.h"

#define RECT_POINT_NUM 4

typedef struct
{
  double min;
  double max;
} MinMax;

typedef struct
{
  int id;
  char name[MAX_NAME];
  MinMax x; // minimum and maximum value of x
  MinMax y; // same for y
  Point points[2];
} Rectangle;

typedef Rectangle *PRect;

typedef struct
{
  PRect *all;
  int size;
  int lastIndex;
} Rectangles;

int computeRectFromPoints(Rectangle *rect, Point p1, Point p2);
int isRectangleValid(Point p1, Point p2);
Rectangles *initializeRectangles(int size);
void freeRectangles(Rectangles *pList);
Rectangle *addRectangle(Rectangles *pList, const int id);
int searchRectById(Rectangles *pList, int id);