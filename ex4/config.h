
#define MAX_WORD_LENGTH 45 // longest word in typical English dictionary is 45 characters long.
#define MAX_FILE_COUNT 10
#define MAX_TERM_COUNT 20

typedef struct
{
  int documentCount;
  int termCount;
  char fileNames[MAX_WORD_LENGTH + 4 + 1][MAX_FILE_COUNT]; // add 4 for ".txt and 1 for null terminator
} Config;

void loadConfig(char *configFile, Config *pConfig);
