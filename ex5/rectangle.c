#include "rectangle.h"

int computeRectFromPoints(Rectangle *rect, Point p1, Point p2)
{
  if (!isRectangleValid(p1, p2))
    return 1;

  rect->x.max = max(p1.x, p2.x);
  rect->x.min = min(p1.x, p2.x);
  rect->y.max = max(p1.y, p2.y);
  rect->y.min = min(p1.y, p2.y);

  // points go in clock-wise from top-left (0 => top-left, 1 => top-right, 2 => bottom-right, 3 => botton-left)
  setPoint(&rect->points[0], rect->x.min, rect->y.max);
  setPoint(&rect->points[1], rect->x.max, rect->y.max);
  setPoint(&rect->points[2], rect->x.max, rect->y.min);
  setPoint(&rect->points[3], rect->x.min, rect->y.min);

  // edges go in clock-wise from top edge (0 => top, 1 => right, 2 => bottom, 3 => left)
  // printPoint(rect->points[0]);
  // printPoint(rect->points[1]);
  // printPoint(rect->points[2]);
  // printPoint(rect->points[3]);

  // top edge
  computeLineFromPoints(&rect->edges[0], (rect->points)[0], (rect->points)[1]);
  // right edge
  computeLineFromPoints(&rect->edges[1], (rect->points)[1], (rect->points)[2]);
  // bottom edge
  computeLineFromPoints(&rect->edges[2], (rect->points)[2], (rect->points)[3]);
  // left edge
  computeLineFromPoints(&rect->edges[3], (rect->points)[3], (rect->points)[0]);

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