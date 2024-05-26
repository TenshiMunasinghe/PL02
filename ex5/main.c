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
    printf("Parsed line %d", count++);
  }

  return EXIT_SUCCESS;
}