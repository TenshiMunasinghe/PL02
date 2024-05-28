#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "shape.h"
#include "utils.h"
#include "line.h"
#include "colors.h"

#define RECT_POINT_NUM 4

typedef struct
{
  double min;
  double max;
} MinMax;

typedef struct
{
  int id;
  char color[MAX_COLOR_CHAR];
  MinMax x;        // minimum and maximum value of x
  MinMax y;        // same for y
  Point points[4]; // points go in clock-wise from top-left (0 => top-left, 1 => top-right, 2 => bottom-right, 3 => botton-left)
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