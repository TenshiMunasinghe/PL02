#include <stdio.h>
#include <math.h>

#include "Point.h"

float distance(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

int readPoint(FILE *fin, Point *pPoint)
{
	int retScan = fscanf(fin,"%f %f", &(pPoint->x), &(pPoint->y));
	if (retScan != 2) return 0; // No point scanned

	return 1; // We got one point
}

void printPoint(FILE *fout, Point point)
{
	// Implement by yourself
	// ...
	printf("(%f, %f)\n", point.x, point.y);
}