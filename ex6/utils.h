#pragma once

#include <math.h>
#include <stdio.h>
#include <ctype.h>

#define DOUBLE_COMPSRISON_THRESHOLD 0.01

double min(double a, double b);
double max(double a, double b);
int compareDouble(double a, double b);
int getToken(FILE *in, char *token, int limit, int (*isValid)(char));
int isDigit(char ch);
int isAlpha(char ch);
