#include <stdio.h>
#include <math.h>

#include "Triangle.h"
#include "Point.h"
#include "Line.h"

int constructTriangle(Triangle* pTriangle, Point p1, Point p2, Point p3)
{
	Line line;

	if (!constructLine(&line, p1, p2)) return 0; // If no line bw p1 and p2, no triangle either

	if (isInLine(line, p3)) return 0; // if p3 belongs to the line, no triangle

	// Here we can construct a valid triangle
	pTriangle->p1 = p1;
	pTriangle->p2 = p2;
	pTriangle->p3 = p3;
}

void computeTriangleArea(Triangle* pTriangle)
{
	float side[3];

	side[0] = distance(pTriangle->p1, pTriangle->p2);
	side[1] = distance(pTriangle->p2, pTriangle->p3);
	side[2] = distance(pTriangle->p1, pTriangle->p3);

	float semiPerim = (side[0] + side[1] + side[2]) / 2;
	pTriangle->area = sqrt(semiPerim*(semiPerim - side[0])*(semiPerim - side[1])*(semiPerim - side[2]));
}

void printTriangleInfo(Triangle triangle)
{
	// Implement by yourself...
	printf("p1: ");
	printf(printPoint(p1));
	printf("p2: ");
	printf(printPoint(p2));
	printf("p2: ");
	printf(printPoint(p2));
	printf("Area of input triangle: %f\n", computeTriangleArea(&triangle));
}
