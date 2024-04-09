#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "point.h"
#include "line.h"
// Include all necessary files you need...

int main()
{
	// Implement by yourself with using types and functions
	// from other modules of this project
	// ...
	Point vertex[3];
	Triangle triangle;

	  for (int i = 0; i <= 2; i++)
  {
    printf("Enter coordinate of vertex %d (separate with a whitespace):", i + 1);
    if (scanf("%f %f", &(vertex[i].x), &(vertex[i].y) != 2))
    {
      printf("Invalid coordinate.\n");
      return EXIT_FAILURE;
    }
  }
	constructTriangle(&triangle, vertex[0], vertex[1], vertex[2]);

}