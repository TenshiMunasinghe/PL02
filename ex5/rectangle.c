#include "rectangle.h"

void isRectanglevalid(Rectangle rect)
{
  for (int i = 0; i < RECT_POINT_NUM - 1; i++)
  {
    for (int j = 0; j < RECT_POINT_NUM - 1; j++)
    {
      if (i == j)
        continue;
      if (isPointEqual(rect[i], rect[i + 1]) == 1)
      {
        printf("Invalid points in rectangle, exiting program\n");
        exit(1);
      }
    }
  }
};
