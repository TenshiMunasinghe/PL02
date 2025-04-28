#include "sort.h"

OutList *initializeOutList(int size)
{
  OutList *pList = (OutList *)malloc(sizeof(OutList));
  if (pList == NULL)
    return NULL;

  pList->all = (POut *)malloc(size * sizeof(POut));
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

void freeOutList(OutList *pList)
{
  for (int ix = 0; ix <= pList->lastIndex; ix++)
  {
    if (pList->all[ix] != NULL)
      free(pList->all[ix]);
  }
  free(pList);
};

Output *addOutput(OutList *pList, const double area, char text[MAX_TEXT_SIZE])
{
  pList->lastIndex++;
  pList->all[pList->lastIndex] = (Output *)malloc(sizeof(Output));
  if (pList->all[pList->lastIndex] == NULL)
    return NULL;
  pList->all[pList->lastIndex]->area = area;
  strcpy(pList->all[pList->lastIndex]->text, text);
  return pList->all[pList->lastIndex];
}

void sortOutput(OutList *pList)
{
  Output temp;
  for (int i = 0; i < pList->lastIndex + 1; ++i)
  {
    for (int j = i + 1; j < pList->lastIndex + 1; ++j)
    {
      if (pList->all[i]->area < pList->all[j]->area)
      {
        // copy all[i] to temp
        temp.area = pList->all[i]->area;
        strcpy(temp.text, pList->all[i]->text);

        // copy all[j] to all[i]
        pList->all[i]->area = pList->all[j]->area;
        strcpy(pList->all[i]->text, pList->all[j]->text);

        // copy temp to all[j]
        pList->all[j]->area = temp.area;
        strcpy(pList->all[j]->text, temp.text);
      }
    }
  }
}

void printSortedOutput(OutList *pList)
{
  sortOutput(pList);

  for (int i = 0; i < pList->lastIndex + 1; ++i)
  {
    printf("%s", pList->all[i]->text);
  }
}