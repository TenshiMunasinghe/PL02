#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

int main()
{
  FILE *in;
  in = fopen("test.txt", "rt");
  if (in == NULL)
  {
    printf("Failed to open input file.\n");
    return EXIT_FAILURE;
  }

  Lines *pLines = initializeLines(20);
  Rectangles *pRects = initializeRectangles(20);

  int count;

  while (parseInput(in, pLines, pRects))
  {
    printf("Parsed line %d\n", count++);
  }

  for (int i = 0; i < pLines->lastIndex + 1; i++)
  {
    printf("%d %s %lf %lf %lf %lf\n", pLines->all[i]->id, pLines->all[i]->name, pLines->all[i]->points[0].x, pLines->all[i]->points[0].y, pLines->all[i]->points[1].x, pLines->all[i]->points[1].y);
  }
  for (int i = 0; i < pRects->lastIndex + 1; i++)
  {
    printf("%d %s %lf %lf %lf %lf\n", pRects->all[i]->id, pRects->all[i]->name, pRects->all[i]->points[0].x, pRects->all[i]->points[0].y, pRects->all[i]->points[1].x, pRects->all[i]->points[1].y);
  }

  return EXIT_SUCCESS;
}