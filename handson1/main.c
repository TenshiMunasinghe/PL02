#include <stdlib.h>
#include "point.h"
#include <stdio.h>

int main()
{
  Point vertex[3];

  for (int i = 0; i <= 2; i++)
  {
    printf("Enter coordinate of vertex %d (separate with a whitespace):", i + 1);
    if (scanf("%f %f", &(vertex[i].x), &(vertex[i].y) != 2))
    {
      printf("Invalid coordinate.\n");
      return EXIT_FAILURE;
    }
  }

  if (isPointEqual(vertex[0], vertex[1]) || isPointEqual(vertex[0], vertex[2]) || isPointEqual(vertex[1], vertex[2]))
  {
    printf("Some vertexes are the same.\n");
    return EXIT_FAILURE;
  }

  // add isLine

  float area = (vertex[0].x * (vertex[1].y - vertex[2].y) + vertex[1].x * (vertex[2].y - vertex[0].y) + vertex[2].x * (vertex[0].y - vertex[1].y)) / 2;

  return EXIT_SUCCESS;
};
