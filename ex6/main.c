#include <stdlib.h>
#include <stdio.h>
#include "parse.h"
#include "intersect.h"
#include "utils.h"
#include "colors.h"
#include "sort.h"

#define MAX_LINE_NUM 20
#define MAX_RECT_NUM 20
#define MAX_OUT_NUM 400

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
  OutList *pOutList = initializeOutList(MAX_OUT_NUM);

  ColorArr colorArray;
  parseColors(colorArray);

  while (parseInput(in, pLines, pRects, colorArray))
  {
  }

  for (int i = 0; i < pRects->lastIndex + 1; i++)
  {
    for (int j = i + 1; j < pRects->lastIndex + 1; j++)
    {
      if (strcmp(pRects->all[i]->color, pRects->all[j]->color) != 0) // Skip if they don't have the same color
        continue;

      double commonArea = computeRectIntersectArea(pRects->all[i], pRects->all[j]);
      if (compareDouble(commonArea, 0) != 1)
      {
        char text[MAX_TEXT_SIZE];
        sprintf(text, "#%d (%s) intercepts with #%d (%s) producing common area %lf\n",
                pRects->all[i]->id, pRects->all[i]->color, pRects->all[j]->id, pRects->all[j]->color, commonArea);
        addOutput(pOutList, commonArea, text);
      }
      else if (computeRectTouching(pRects->all[i], pRects->all[j]) == 1)
      {
        char text[MAX_TEXT_SIZE];
        sprintf(text, "#%d (%s) intercepts with #%d (%s) producing common area %lf\n",
                pRects->all[i]->id, pRects->all[i]->color, pRects->all[j]->id, pRects->all[j]->color, commonArea);
        addOutput(pOutList, commonArea, text);
      }
    }
  }

  // sort and print remaining output
  printSortedOutput(pOutList);

  for (int i = 0; i < pLines->lastIndex + 1; i++)
  {
    // compare lines with lines
    for (int j = i + 1; j < pLines->lastIndex + 1; j++)
    {
      if (strcmp(pLines->all[i]->color, pLines->all[j]->color) != 0) // Skip if they don't have the same color
        continue;

      if (computeLineIntersect(pLines->all[i]->points, pLines->all[j]->points) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pLines->all[i]->id, pLines->all[i]->color, pLines->all[j]->id, pLines->all[j]->color);
      }
    }

    // compare lines with rectangles
    for (int j = 0; j < pRects->lastIndex + 1; j++)
    {
      if (strcmp(pLines->all[i]->color, pRects->all[j]->color) != 0) // Skip if they don't have the same color
        continue;

      if (computeLineRectIntersect(pLines->all[i], pRects->all[j]) == 1)
      {
        printf("#%d (%s) intercepts with #%d (%s) producing common area 0\n",
               pLines->all[i]->id, pLines->all[i]->color, pRects->all[j]->id, pRects->all[j]->color);
      }
    }
  }

  fclose(in);
  freeLines(pLines);
  freeRectangles(pRects);
  freeOutList(pOutList);

  return EXIT_SUCCESS;
}