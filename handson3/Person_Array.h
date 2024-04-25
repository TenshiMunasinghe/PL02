#pragma once

#include <stdio.h>

#include "Person.h"
#define BIRTH_YEAR_LIMIT 2016

int countRecords(FILE *in, FILE *fBin);
void createIdxArr(int **pArr, int length);
int loadRecordsFromTextFile(FILE *in, Person *all, int size);
int loadRecordsFromBinary(FILE *fBin, Person *all, int size);
void calculateAges(Person *all, int size, const Date *current);
void printRecords(const char *title, FILE *out, const Person *all, int size,
                  char *dateFormat);
void printRecordsByIdx(const char *title, FILE *out, const Person *all,
                       int *pIdxArr, int size, char *dateFormat);
