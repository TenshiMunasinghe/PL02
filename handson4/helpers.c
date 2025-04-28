// Helper functions for music

#include "cs50.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

int velocity(string velocity_str)
{
    int default_velocity = 100;
    if (velocity_str == NULL)
    {
        return default_velocity;
    }

    int v = atoi(velocity_str);
    if (v >= 1 && v <= 127)
    {
        return v;
    }

    return default_velocity;
}

// Converts a fraction formatted as X/Y to eighths and extracts velocity
int duration(string fraction)
{
    int numerator, denominator;

    // Validate input format
    if (fraction == NULL || sscanf(fraction, "%d/%d", &numerator, &denominator) != 2)
    {
        return 0; // Return 0 for invalid input
    }

    // Check for division by zero
    if (denominator == 0)
    {
        return 0;
    }

    return (numerator * 8) / denominator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    if (note == NULL || strlen(note) < 2)
    {
        return 0; // Return 0 for invalid input
    }

    double frequency = 16.35; // start with C on 0 octave
    int strPos = 0;

    // Validate note letter
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
        return 0; // Return 0 for invalid note
    }

    strPos++;

    // Handle accidentals
    if (note[strPos] == '#')
    {
        frequency *= pow(2, (double)1 / 12);
        strPos++;
    }
    else if (note[strPos] == 'b')
    {
        frequency *= pow(2, (double)(-1) / 12);
        strPos++;
    }

    // Validate octave
    if (note[strPos] < '0' || note[strPos] > '9')
    {
        return 0; // Return 0 for invalid octave
    }

    int octave = note[strPos] - '0';
    frequency *= pow(2, octave);

    return (int)frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return (s == NULL || s[0] == '\0' || strcmp(s, "") == 0);
}
