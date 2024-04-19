#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool isValidName(char *name) {
  while (*name) {
    if (!isalpha(*name))
      return false;
    name++;
  }
  return true;
}

bool isValidId(char *id) {
  while (*id) {
    if (!isalpha(*id) && !isdigit(*id)) {
      return false;
    }
    id++;
  }
  return true;
}

// Names are words containing only letters
int getName(FILE *in, char *name, int limit) {
  char ch = fgetc(in);
  int ixLit = 0;

  // Skip leading spaces
  while (isspace(ch))
    ch = fgetc(in);
  if (ch == EOF)
    return EOF;
  // Reading a word of letters
  while (!isspace(ch) && ch != EOF) {
    if (!isalpha(ch))
      return 0;

    if (ixLit < limit)
      name[ixLit++] = ch;

    ch = fgetc(in);
  }
  name[ixLit] = '\0';

  return 1;
}

// IDs are words contaning letters and digits
int getId(FILE *in, char *id, int limit) {
  // Complete this function definition
  // similar to getName()
  // ...
  char ch = fgetc(in);
  int ixLit = 0;

  // Skip leading spaces
  while (isspace(ch))
    ch = fgetc(in);
  if (ch == EOF)
    return EOF;
  // Reading a word of letters
  while (!isspace(ch) && ch != EOF) {
    if (!isalpha(ch) && !isdigit(ch))
      return 0;

    if (ixLit < limit)
      id[ixLit++] = ch;

    ch = fgetc(in);
  }
  id[ixLit] = '\0';

  return 1;
}
