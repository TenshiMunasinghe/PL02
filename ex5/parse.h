#include "line.h"
#include "rectangle.h"

#include <string.h>
#include <ctype.h>

#define MAX_ID_DIGIT 4 // maximum ID is 100
#define MAX_TYPE 11
#define MAX_NAME 13
#define MAX_TOKEN_SIZE 16

int parseInput(FILE *in, Lines lines, Rectangles rects);