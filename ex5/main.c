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

  int i = 0;
  while (parseInput(in, lines, rects))
  {
    printf("%d\n", i++);
  }
  return EXIT_SUCCESS;
}