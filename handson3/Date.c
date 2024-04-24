#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Date.h"
#include "Person_Array.h"
#include "String_Oper.h"

#define DATE_TEXT_SIZE 50

const char monthNames[12][10] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

int isLeapYear(int year); // See the function definition below...

int readDate(FILE *in, Date *pDate) {
  int retScan =
      fscanf(in, "%d %d %d", &(pDate->year), &(pDate->month), &(pDate->day));
  if (retScan == EOF)
    return EOF;
  if (retScan != 3)
    return 0;
  return 1;
}

bool isDateLegal(const Date *pDate, int yearLimit) {
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

void printDate(FILE *out, const Date *pDate, char *format) {
  // Complete this function
  // ...
  char dateStr[DATE_TEXT_SIZE];
  formatDate(dateStr, format, *pDate);
  fprintf(out, "%s", dateStr);
}

void printDateLine(FILE *out, const Date *pDate, char *format) {
  printDate(out, pDate, format);
  fprintf(out, "\n");
}

int getAge(const Date *pBirthDate, const Date *pCurrent) {
  int age;

  age = pCurrent->year - pBirthDate->year;
  if (age <= 0) {
    age = 0;
    return age;
  }

  // Write missting code to compute age
  // ...
  if (pCurrent->month > pBirthDate->month) {
    return age;
  }

  if (pCurrent->month == pBirthDate->month &&
      pCurrent->day >= pBirthDate->day) {
    return age;
  }

  return age - 1;
}

// Complete definition of this function:
// Function returns 1, if the year is leap,
//          returns 0. otherwise
int isLeapYear(int year) {
  if (year % 400 == 0)
    return 1;

  else if (year % 100 == 0)
    return 0;

  else if (year % 4 == 0)
    return 1;

  return 0;
}

int formatDate(char result[DATE_TEXT_SIZE], char *format, Date date) {
  struct tm time;
  time.tm_year = date.year - 1900;
  time.tm_mon = date.month - 1;
  time.tm_mday = date.day;

  char *temp = strdup(format);

  if (!isDateLegal(&date, BIRTH_YEAR_LIMIT)) {
    return 0;
  }

  // replace day
  if (strstr(temp, "dd") != NULL) {
    replace(temp, "dd", "%d");
  } else if (strstr(temp, "d") != NULL) {
    replace(temp, "d", "%e");
  }

  // replace month
  if (strstr(temp, "mmmm") != NULL) {
    replace(temp, "mmmm", "%B");
  } else if (strstr(temp, "mmm") != NULL) {
    replace(temp, "mmm", "%b");
  } else if (strstr(temp, "mm") != NULL) {
    replace(temp, "mm", "%m");
  }

  // replace day
  if (strstr(temp, "yyyy") != NULL) {
    replace(temp, "yyyy", "%Y");
  } else if (strstr(temp, "yy") != NULL) {
    replace(temp, "yy", "%y");
  }

  strftime(result, DATE_TEXT_SIZE, temp, &time);
  // strcpy(result, temp);

  return 1;
}
