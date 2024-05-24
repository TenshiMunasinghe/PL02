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

  Lines lines;
  Rectangles rects;

  while (parseInput(in, lines, rects))
  {
  }
  return EXIT_SUCCESS;
}