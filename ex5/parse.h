#pragma once

#include "line.h"
#include "rectangle.h"
#include "shape.h"

#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 256

int parseInput(FILE *in, Lines *lines, Rectangles *rects);