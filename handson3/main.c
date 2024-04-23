#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Config.h"
#include "Person.h"
#include "Person_Array.h"
#include "Sort.h"

int main(int argc, char **argv)
{
  if (!argv[1])
  {
    printf("Enter config file name.\n");
    return EXIT_FAILURE;
  }

  Config *pConfig;
  pConfig = (Config *)malloc(sizeof(Config));

  loadConfig(argv[1], pConfig);

  FILE *in, *out, *binIn, *binOut;
  Person *all;
  int numOfPersons;

  in = fopen(pConfig->inputFile, "rt");
  if (in == NULL)
  {
    printf("Unable to open input file\n");
    return EXIT_FAILURE;
  }

  out = fopen(pConfig->outputFile, "wt");
  if (out == NULL)
  {
    printf("Unable to open output file\n");
    return EXIT_FAILURE;
  }

  binOut = fopen("temp.bin", "wb");
  if (binOut == NULL)
  {
    printf("Unable to open binary file\n");
    return EXIT_FAILURE;
  }

  numOfPersons = countRecords(in, binOut);

  binIn = fopen("temp.bin", "rb");
  if (binIn == NULL)
  {
    printf("Unable to open binary file\n");
    return EXIT_FAILURE;
  }

  if (numOfPersons == 0)
  {
    printf("No data in input file\n");
    return EXIT_FAILURE;
  }

  all = (Person *)malloc(numOfPersons * sizeof(Person));
  if (all == NULL)
  {
    printf("Memory allocation error\n");
    return EXIT_FAILURE;
  }

  rewind(in);

  // int count = loadRecordsFromTextFile(in, all, numOfPersons);
  int count = loadRecordsFromBinary(binIn, all, numOfPersons);

  if (count != numOfPersons)
  {
    printf("Unknown error. Please contact the developer\n");
    return EXIT_FAILURE;
  }

  fclose(in);

  calculateAges(all, numOfPersons, &(pConfig->currentDate));

  // printRecords("Records loaded from input file", out, all, numOfPersons);

  if (strcmp(pConfig->sortOrder, "name") == 0)
  {
    sortByName(all, numOfPersons);
    printRecords("Records sorted by name", out, all, numOfPersons);
  }
  else if (strcmp(pConfig->sortOrder, "age") == 0)
  {
    sortByAge(all, numOfPersons);
    printRecords("Records sorted by age", out, all, numOfPersons);
  }
  else
  {
    printRecords("No sorting order specified", out, all, numOfPersons);
  }

  free(all);
  return EXIT_SUCCESS;
}
