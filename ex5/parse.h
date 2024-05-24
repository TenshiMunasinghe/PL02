#include "line.h"
#include "rectangle.h"

#define MAX_ID_DIGIT 3 // maximum ID is 100
#define MAX_TYPE 10
#define MAX_NAME 12
#define MAX_TOKEN_SIZE 16

int parseInput(FILE *in, Lines lines, Rectangles rects);