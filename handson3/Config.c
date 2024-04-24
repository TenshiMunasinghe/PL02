#include "Config.h"
#include <stdlib.h>
#include <string.h>

#define YEAR_LIMIT 2024

void loadConfig(char *configFile, Config *pConfig) {
  FILE *config;
  config = fopen(configFile, "rt");

  if (config == NULL) {
    printf("Failed to find config file.\n");
    exit(1);
  }

  int retScan;

  retScan = fscanf(config, "%s", pConfig->inputFile);
  if (retScan != 1) {
    printf("Error in reading input file name.\n");
    exit(1);
  }

  retScan = fscanf(config, "%s", pConfig->outputFile);
  if (retScan != 1) {
    printf("Error in reading output file name.\n");
    exit(1);
  };

  retScan = fscanf(config, "%d/%d/%d", &(pConfig->currentDate.year),
                   &(pConfig->currentDate.month), &(pConfig->currentDate.day));
  if (retScan != 3 || !isDateLegal(&(pConfig->currentDate), YEAR_LIMIT)) {
    printf("Error in reading current date.\n");
    exit(1);
  };

  retScan = fscanf(config, "%s", pConfig->dateFormat);
  if (retScan != 1) {
    strcpy(pConfig->dateFormat, "yyyy/mm/dd"); // default format
  };

  retScan = fscanf(config, "%s", pConfig->sortOrder);
  // allow user to NOT specify any sort order.
  // if (retScan != 1)
  // {
  //   printf("Error in reading sort order.\n");
  //   exit(1);
  // };
};
