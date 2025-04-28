#pragma once

#include "Point.h"

typedef struct
{
	Point p1, p2, p3;
	float area;
} Triangle;

int constructTriangle(Triangle* pTriangle, Point p1, Point p2, Point p3);
void computeTriangleArea(Triangle *pTriangle);
void printTriangleInfo(Triangle triangle);