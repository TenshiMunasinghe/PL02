#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
  // Complete definition according
  // to hands-on materials
  // ...
  int year;
  int month;
  int day;
} Date;

int readDate(FILE *in, Date *pDate);
bool isDateLegal(const Date *pDate, int yearLimit);
void printDate(FILE *out, const Date *pDate);
void printDateLine(FILE *out, const Date *pDate);
int getAge(const Date *pDate, const Date *pCurrent);
int formatDate(char *result, char *format, Date date);