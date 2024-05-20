// Helper functions for music

#include "cs50.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator, denominator;

    sscanf(fraction, "%d/%d", &numerator, &denominator);

    return (numerator * 8) / denominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double frequency = 16.35; // start with C on 0 octave
    int strPos = 0;

    switch (note[strPos])
    {
    case 'C':
        break;
    case 'D':
        frequency *= pow(2, (double)2 / 12);
        break;
    case 'E':
        frequency *= pow(2, (double)4 / 12);
        break;
    case 'F':
        frequency *= pow(2, (double)5 / 12);
        break;
    case 'G':
        frequency *= pow(2, (double)7 / 12);
        break;
    case 'A':
        frequency *= pow(2, (double)9 / 12);
        break;
    case 'B':
        frequency *= pow(2, (double)11 / 12);
        break;
    default:
        break;
    }

    strPos++;

    if (note[strPos] == '#')
    {
        frequency *= pow(2, (double)1 / 12);
        strPos++;
    }

    char octave[2] = {note[strPos], '\0'}; // convert char to string
    frequency *= pow(2, atof(octave));     // here, note[strPos] is the number before '@'

    return (int)frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    return strcmp(s, "\0") == 0;
}
