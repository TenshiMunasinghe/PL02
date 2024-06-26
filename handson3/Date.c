#include <stdbool.h>
#include <stdio.h>

#include "Date.h"

int isLeapYear(int year); // See the function definition below...

int readDate(FILE *in, Date *pDate)
{
  int retScan =
      fscanf(in, "%d %d %d", &(pDate->year), &(pDate->month), &(pDate->day));
  if (retScan == EOF)
    return EOF;
  if (retScan != 3)
    return 0;
  return 1;
}

bool isDateLegal(const Date *pDate, int yearLimit)
{
  int daysLimit[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  bool isLegal = true;

  if ((pDate->month < 1) || (pDate->month > 12))
    isLegal = false;
  else if ((pDate->day < 1) || (pDate->day > daysLimit[pDate->month - 1]))
    isLegal = false;
  else if ((pDate->year < 1900) || (pDate->year > yearLimit))
    isLegal = false;
  else if ((pDate->month == 2) && (pDate->day == 29) &&
           (!isLeapYear(pDate->year)))
    isLegal = false;
  return isLegal;
}

void printDate(FILE *out, const Date *pDate)
{
  // Complete this function
  // ...
  fprintf(out, "%d/%d/%d", pDate->year, pDate->month, pDate->day);
}

void printDateLine(FILE *out, const Date *pDate)
{
  printDate(out, pDate);
  fprintf(out, "\n");
}

int getAge(const Date *pBirthDate, const Date *pCurrent)
{
  int age;

  age = pCurrent->year - pBirthDate->year;
  if (age <= 0)
  {
    age = 0;
    return age;
  }

  // Write missting code to compute age
  // ...
  if (pCurrent->month > pBirthDate->month)
  {
    return age;
  }

  if (pCurrent->month == pBirthDate->month &&
      pCurrent->day >= pBirthDate->day)
  {
    return age;
  }

  return age - 1;
}

// Complete definition of this function:
// Function returns 1, if the year is leap,
//          returns 0. otherwise
int isLeapYear(int year)
{
  if (year % 400 == 0)
    return 1;

  else if (year % 100 == 0)
    return 0;

  else if (year % 4 == 0)
    return 1;

  return 0;
}
