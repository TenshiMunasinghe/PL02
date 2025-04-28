#pragma once

#include "line.h"
#include "rectangle.h"
#include "shape.h"
#include "colors.h"

#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 256

int parseInput(FILE *in, Lines *lines, Rectangles *rects, ColorArr colorArray);
int getToken(FILE *in, char *token, int limit, int (*isValid)(char));
void getRestOfLineWithoutSpace(FILE *in, char token[256], int limit);
int parsePoints(char token[MAX_TOKEN_SIZE], Point *p1, Point *p2);
int isValidNumChar(char ch);