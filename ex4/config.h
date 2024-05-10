
#define MAX_FILE_COUNT 10
#define MAX_TERM_COUNT 20

typedef struct
{
  int numDocs;
  int numTerms;
  char **fileNames; // add 1 for null terminator
} Config;

void loadConfig(char *configFile, Config *pConfig);
