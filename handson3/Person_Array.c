#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Date.h"
#include "Person.h"
#include "String_Oper.h"

int countRecords(FILE *in, FILE *fBin) {
  int count = 0;

  for (;;) {
    Person temp;
    int checkRead = readPerson(in, &temp);
    if (checkRead == EOF) {
      fclose(fBin);
      return count;
    }
    if (checkRead != 1) {
      printf("Illegal format for the record No.%d\n", count + 1);
      exit(1);
    }
    fwrite(&temp, sizeof(Person), 1, fBin);
    ++count;
  }
}

int loadRecordsFromTextFile(FILE *in, Person *all, int size) {
  int count;

  for (count = 0; count < size; ++count) {
    // Complete this loop body
    // (use readPerson() function to read the array element.
    // Do not forget to check the value returned by readPerson() and
    // print messages in case of reading errors.
    // Stop program by using exit(1) if reading errors are detected.
    // ...
    Person *pPerson;
    pPerson = all + count;
    if (pPerson == NULL) {
      printf("Memory allocation error\n");
      exit(1);
    }

    readPerson(in, pPerson);
    if (!isDateLegal(&(pPerson->birthDate), 2016) ||
        !isValidName(pPerson->name) || !isValidId(pPerson->id)) {
      printf("Illegal value read from input file.\n");
      exit(1);
    }
  }
  return count;
}

int loadRecordsFromBinary(FILE *fBin, Person *all, int size) {
  return fread(all, sizeof(Person), size, fBin);
}

void printRecords(const char *title, FILE *out, const Person *all, int size,
                  char *dateFormat) {
  fprintf(out, "%s\n", title);

  for (int ix = 0; ix < size; ++ix) {
    printPersonLine(out, &(all[ix]), dateFormat);
  }
}

void calculateAges(Person *all, int size, const Date *pCurrent) {
  // By using getAge() function
  // calculate the ages of all the persons in the array "all"
  // ...
  for (int i = 0; i < size; i++) {
    all[i].age = getAge(&(all[i].birthDate), pCurrent);
  }
}
