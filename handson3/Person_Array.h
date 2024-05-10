#pragma once

#include <stdio.h>

#include "Person.h"

int countRecords(FILE *in, FILE *fBin);
int loadRecordsFromTextFile(FILE *in, Person *all, int size);
int loadRecordsFromBinary(FILE *fBin, Person *all, int size);
void calculateAges(Person *all, int size, const Date *current);
void printRecords(const char *title, FILE *out, const Person *all, int size);
