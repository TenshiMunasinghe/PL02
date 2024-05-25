#include "rectangle.h"

int computeRectFromPoints(Rectangle *rect, Point p1, Point p2)
{
  if (!isRectangleValid(p1, p2))
    return 1;

  rect->points[0].x = p1.x;
  rect->points[0].y = p1.y;

  rect->points[0].x = p2.x;
  rect->points[0].y = p2.y;

  rect->points[0].x = p1.x;
  rect->points[0].y = p2.y;

  rect->points[0].x = p2.x;
  rect->points[0].y = p1.y;

  return 0;
};

int isRectangleValid(Point p1, Point p2)
{
  if (p1.x == p2.x || p1.y == p2.y)
  {
    printf("Invalid points in rectangle, exiting program\n");
    exit(1);
  }
  return 1;
};

Rectangles *initializeRectangles(int size)
{
  Rectangles *pList = (Rectangles *)malloc(sizeof(Rectangles));
  if (pList == NULL)
    return NULL;

  pList->all = (PRect *)malloc(size * sizeof(PRect));
  if (pList->all == NULL)
  {
    free(pList);
    return NULL;
  }

  for (int ix = 0; ix < size; ix++)
  {
    pList->all[ix] = NULL;
  }

  pList->size = size;
  pList->lastIndex = -1;
  return pList;
}

void freeRectangles(Rectangles *pList)
{
  for (int ix = 0; ix <= pList->lastIndex; ix++)
  {
    if (pList->all[ix] != NULL)
      free(pList->all[ix]);
  }
  free(pList);
};

Rectangle *addRectangle(Rectangles *pList, const int id)
{
  int ixFound;
  if ((ixFound = searchRectById(pList, id)) != -1)
  {
    return pList->all[ixFound];
  }
  pList->lastIndex++;
  pList->all[pList->lastIndex] = (Rectangle *)malloc(sizeof(Rectangle));
  if (pList->all[pList->lastIndex] == NULL)
    return NULL;
  pList->all[pList->lastIndex]->id = id;
  return pList->all[pList->lastIndex];
}

int searchRectById(Rectangles *pList, int id)
{
  for (int ix = 0; ix <= pList->lastIndex; ix++)
  {
    if (pList->all[ix]->id == id)
      return ix;
  }
  return -1;
};