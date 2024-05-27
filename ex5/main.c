#include <stdlib.h>
#include <stdio.h>
#include "parse.h"
#include "intersect.h"
#include "utils.h"

#define MAX_LINE_NUM 20
#define MAX_RECT_NUM 20

int main()
{
  FILE *in;
  in = fopen("test.txt", "rt");
  if (in == NULL)
  {
    printf("Failed to open input file.\n");
    return EXIT_FAILURE;
  }

  Lines *pLines = initializeLines(MAX_LINE_NUM);
  Rectangles *pRects = initializeRectangles(MAX_RECT_NUM);

  int count;

  while (parseInput(in, pLines, pRects))
  {
  }

  // debug code for printing parsed data
  // for (int i = 0; i < pLines->lastIndex + 1; i++)
  // {
  //   printf("%d %s %lf %lf %lf %lf %lf %lf %lf\n", pLines->all[i]->id, pLines->all[i]->name, pLines->all[i]->properties.points[0].x, pLines->all[i]->properties.points[0].y, pLines->all[i]->properties.points[1].x, pLines->all[i]->properties.points[1].y, pLines->all[i]->properties.a, pLines->all[i]->properties.b, pLines->all[i]->properties.c);
  // }
  // for (int i = 0; i < pRects->lastIndex + 1; i++)
  // {
  //   printf("%d %s %lf %lf %lf %lf %lf %lf %lf\n", pRects->all[i]->id, pRects->all[i]->name, pRects->all[i]->points[0].x, pRects->all[i]->points[0].y, pRects->all[i]->points[1].x, pRects->all[i]->points[1].y, pRects->all[i]->edges[0].a, pRects->all[i]->edges[0].b, pRects->all[i]->edges[0].c);
  // }

  for (int i = 0; i < pLines->lastIndex + 1; i++)
  {
    // compare lines with lines
    for (int j = i + 1; j < pLines->lastIndex + 1; j++)
    {
      if (computeLineIntersect(&(pLines->all[i]->properties), &(pLines->all[j]->properties)) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pLines->all[i]->id, pLines->all[i]->name, pLines->all[j]->id, pLines->all[j]->name);
      }
    }

    // compare lines with rectangles
    for (int j = 0; j < pRects->lastIndex + 1; j++)
    {
      if (computeLineRectIntersect(&(pLines->all[i]->properties), pRects->all[j]) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pLines->all[i]->id, pLines->all[i]->name, pRects->all[j]->id, pRects->all[j]->name);
      }
    }
  }

  for (int i = 0; i < pRects->lastIndex + 1; i++)
  {
    for (int j = i + 1; j < pRects->lastIndex + 1; j++)
    {
      double commonArea = computeRectIntersectArea(pRects->all[i], pRects->all[j]);
      if (compareDouble(commonArea, 0) != 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area %lf\n",
               pRects->all[i]->id, pRects->all[i]->name, pRects->all[j]->id, pRects->all[j]->name, commonArea);
      }
      else if (computeRectTouching(pRects->all[i], pRects->all[j]) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pRects->all[i]->id, pRects->all[i]->name, pRects->all[j]->id, pRects->all[j]->name);
      }
    }
  }
  return EXIT_SUCCESS;
}