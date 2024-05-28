#pragma once

#include "utils.h"
#include <stdio.h>
#include <string.h>

#define MAX_COLOR_CHAR 30
#define MAX_COLOR_NUM 20


typedef char ColorArr[MAX_COLOR_CHAR][MAX_COLOR_NUM];

int parseColors(ColorArr colorArray);
int isColorValid(char *color, ColorArr arr);