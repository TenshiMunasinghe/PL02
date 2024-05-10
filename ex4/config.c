#include "config.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>

void loadConfig(char *configFile, Config *pConfig)
{
  FILE *config;
  config = fopen(configFile, "rt");

  if (config == NULL)
  {
    printf("Failed to find config file.\n");
    exit(1);
  }

  int retScan;

  retScan = fscanf(config, "%d", &(pConfig->numDocs));
  if (retScan != 1)
  {
    printf("Error in reading number of documents.\n");
    exit(1);
  }
  if (pConfig->numDocs > MAX_FILE_COUNT)
  {
    printf("Maximum number of documents is %d.\n", MAX_FILE_COUNT);
    exit(1);
  }

  retScan = fscanf(config, "%d", &(pConfig->numTerms));
  if (retScan != 1)
  {
    printf("Error in reading number of terms.\n");
    exit(1);
  }
  if (pConfig->numDocs > MAX_TERM_COUNT)
  {
    printf("Maximum number of terms is %d.\n", MAX_TERM_COUNT);
    exit(1);
  }

  // get all the file names in config file

  pConfig->fileNames = (char **)malloc(pConfig->numDocs * sizeof(char *));
  if (pConfig->fileNames == NULL)
  {
    printf("Memory allocation error\n");
    exit(20);
  }

  for (int i = 0; i < pConfig->numDocs; i++)
  {
    pConfig->fileNames[i] = (char *)malloc(MAX_LENGTH + 1);
    if (pConfig->fileNames[i] == NULL)
    {
      printf("Memory allocation error\n");
      exit(20);
    }
  }

  for (int i = 0; i < pConfig->numDocs; i++)
  {
    if (i > MAX_FILE_COUNT - 1)
    {
      printf("Maximum number of documents is %d.\n", MAX_FILE_COUNT);
      exit(1);
    }

    char fileName[MAX_LENGTH];
    fscanf("%s", fileName);
    strcpy(pConfig->fileNames[i], fileName);
  }
};
