#include "rectangle.h"

void isRectanglevalid(Rectangle rect)
{
  for (int i = 0; i < 3; i++)
  {
    if (isPointEqual(rect[i], rect[i + 1]) == 1)
    {
      printf("Invalid points in rectangle, exiting program\n");
      exit(1);
    }
  }
};
