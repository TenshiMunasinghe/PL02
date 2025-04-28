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

  for (int i = 0; i < pLines->lastIndex + 1; i++)
  {
    // compare lines with lines
    for (int j = i + 1; j < pLines->lastIndex + 1; j++)
    {
      if (computeLineIntersect(pLines->all[i]->points, pLines->all[j]->points) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pLines->all[i]->id, pLines->all[i]->name, pLines->all[j]->id, pLines->all[j]->name);
      }
    }

    // compare lines with rectangles
    for (int j = 0; j < pRects->lastIndex + 1; j++)
    {
      if (computeLineRectIntersect(pLines->all[i], pRects->all[j]) == 1)
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