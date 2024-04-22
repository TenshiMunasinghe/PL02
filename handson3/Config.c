#include "Config.h"
#include <stdlib.h>

void loadConfig(char *configFile, Config *pConfig) {
  FILE *config;
  config = fopen(configFile, "rt");

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
  if (retScan != 3) {
    printf("Error in reading current date.\n");
    exit(1);
  };

  retScan = fscanf(config, "%s", pConfig->sortOrder);
  if (retScan != 1) {
    printf("Error in reading sort order.\n");
    exit(1);
  };
};
