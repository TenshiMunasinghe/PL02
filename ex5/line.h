#pragma once

#include "point.h"
#include "shape.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  int id;
  char name[MAX_NAME];
  double a;
  double b;
  double c;
  Point points[2];
} Line; // In form of ax+by=c

typedef Line *PLine;

typedef struct
{
  int size;
  PLine *all;
  int lastIndex;
} Lines;

int computeLineFromPoints(Line *line, Point p1, Point p2);
Lines *initializeLines(int size);
void freeLines(Lines *pList);
Line *addLine(Lines *pList, const int id);
int searchLineById(Lines *pList, int id);