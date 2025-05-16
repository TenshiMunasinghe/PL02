// Helper functions for music

#include "cs50.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// start ADDED
int velocity(string velocity_str)
{
    if (velocity_str == NULL)
        return 0;
    // Default velocity to 100 if not specified
    int velocity = atoi(velocity_str);
    if (velocity < 0)
        velocity = 0;
    if (velocity > 127)
        velocity = 127;
    return velocity;
}
// end ADDED

// Converts a fraction formatted as X/Y to 32ths
int duration(string fraction)
{
    if (fraction == NULL)
        return 0;

    int numerator, denominator;

    sscanf(fraction, "%d/%d", &numerator, &denominator);

    return (numerator * 32) / denominator;
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
    else if (note[strPos] == 'b')
    {
        frequency *= pow(2, (double)(-1) / 12);
        strPos++;
    }

    char octave[2] = {note[strPos], '\0'}; // convert char to string
    frequency *= pow(2, atof(octave));     // here, note[strPos] is the number before '@'
    return (int)frequency;                 // The program did not work on university computer octaves 3 and below although the calculated frequencies are correct.
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s == NULL)
        return false;

    // Check if it starts with "rest@"
    if (strncmp(s, "rest@", 5) == 0 || strcmp(s, "\0") == 0) // For backward compatibility, also check for empty string
        return true;

    return false;
}

// Parses duration from a rest string (e.g., "rest@1/4" returns 2)
int parse_rest_duration(string s)
{
    if (s == NULL)
        return 1; // Default to 1/8 for backward compatibility

    // If it's an empty string, return 1 (1/8)
    if (strcmp(s, "\0") == 0)
    {
        return 1;
    }

    // Parse duration from "rest@X/Y" format
    char *fraction = strchr(s, '@');
    if (fraction == NULL)
        return 1;

    fraction++; // Skip the @
    return duration(fraction);
}
