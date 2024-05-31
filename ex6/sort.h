#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_TEXT_SIZE 256

typedef struct
{
  double area;
  char text[MAX_TEXT_SIZE];
} Output;

typedef Output *POut;

typedef struct
{
  POut *all;
  int size;
  int lastIndex;
} OutList;

OutList *initializeOutList(int size);
void freeOutList(OutList *pList);
Output *addOutput(OutList *pList, const double area, char text[MAX_TEXT_SIZE]);
void sortOutput(OutList *pList);
void printSortedOutput(OutList *pList);