#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "shape.h"

#define RECT_POINT_NUM 4

typedef struct
{
  int id;
  char name[MAX_NAME];
  Point points[4];
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