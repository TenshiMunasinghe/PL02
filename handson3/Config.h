#include "Date.h"

typedef struct {
  char inputFile[20];
  char outputFile[20];
  Date currentDate;
  char sortOrder[10];
} Config;

void loadConfig(char *configFile, Config *pConfig);
