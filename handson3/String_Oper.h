#pragma once

#include <stdio.h>

int getName(FILE *in, char *name, int limit);
int getId(FILE *in, char *id, int limit);
bool isValidName(char *name);
bool isValidId(char *name);
