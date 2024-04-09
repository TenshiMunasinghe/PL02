#pragma once

#include <stdio.h>

// 2D point
typedef struct
{
	float x;
	float y;
} Point;

float distance(Point p1, Point p2);

int readPoint(FILE *fin, Point *pPoint);
int printPoint(FILE *fout, Point point);
