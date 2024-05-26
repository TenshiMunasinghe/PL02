#include "line.h"

int computeLineFromPoints(LineProperties *line, Point p1, Point p2)
{
  if (isPointEqual(p1, p2) == 1)
  {
    printf("Same points detected for line construction, ignoring input.\n");
    return 1;
  }
  setPoint(&(line->points[0]), p1.x, p1.y);
  setPoint(&(line->points[1]), p2.x, p2.y);

  // compute coefficients
  if (compareDouble(p1.x, p2.x) == 1) // line is in form x=c
  {
    line->a = 1;
    line->b = 0;
    line->c = p1.x;
  }
  else if (compareDouble(p1.y, p2.y) == 1) // line is in form y=c
  {
    line->a = 0;
    line->b = 1;
    line->c = p1.y;
  }
  else
  { // line is in form ax+by=c (y=mx+c <=> y-mx=c)
    double gradient = (p1.y - p2.y) / (p1.x - p2.x);
    double intercept = p1.y - (gradient * p1.x);

    line->b = 1;             // coefficient of y
    line->a = gradient * -1; // coefficient of x
    line->c = intercept;
  }

  return 0;
};

Lines *initializeLines(int size)
{
  Lines *pList = (Lines *)malloc(sizeof(Lines));
  if (pList == NULL)
    return NULL;

  pList->all = (PLine *)malloc(size * sizeof(PLine));
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

void freeLines(Lines *pList)
{
  for (int ix = 0; ix <= pList->lastIndex; ix++)
  {
    if (pList->all[ix] != NULL)
      free(pList->all[ix]);
  }
  free(pList);
};

Line *addLine(Lines *pList, const int id)
{
  int ixFound;
  if ((ixFound = searchLineById(pList, id)) != -1)
  {
    return pList->all[ixFound];
  }
  pList->lastIndex++;
  pList->all[pList->lastIndex] = (Line *)malloc(sizeof(Line));
  if (pList->all[pList->lastIndex] == NULL)
    return NULL;
  pList->all[pList->lastIndex]->id = id;
  return pList->all[pList->lastIndex];
}

int searchLineById(Lines *pList, int id)
{
  for (int ix = 0; ix <= pList->lastIndex; ix++)
  {
    if (pList->all[ix]->id == id)
      return ix;
  }
  return -1;
};