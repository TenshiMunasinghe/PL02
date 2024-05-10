/*
 * File:   common.h
 * Author: pyshe
 *
 * Created on May 17, 2019, 9:19 AM
 */

#pragma once

#define MAX_LENGTH 256

typedef struct
{
    char name[MAX_LENGTH];
    FILE *source;

} Document;

int getWord(FILE *f, char *word, int limit);
