// A simple sound library adapted from Douglas Thain's (dthain@nd.edu)
// wavfile library for CSE 20211 made available under the
// Creative Commons Attribution license.
// https://creativecommons.org/licenses/by/4.0/

#ifndef WAV_H
#define WAV_H

#include "cs50.h"
#include <stdio.h>
#include <inttypes.h>

// Represents a note in a song
typedef struct note
{
    int frequency; // Frequency in Hz
    int duration;  // Duration in eighths
    int velocity;  // Velocity (1-127)
} note;

// Represents a song
typedef struct song
{
    string filename; // Name of WAV file
    note **notes;    // Array of notes
    size_t size;     // Number of notes
    size_t capacity; // Capacity of array
    size_t duration; // Total duration in eighths
} *song;

// Opens a new song
song song_open(string filename);

// Writes a note to a song
bool note_write(song s, int frequency, int duration, int velocity);

// Writes a rest to a song
bool rest_write(song s, int duration);

// Closes a song
bool song_close(song s);

#endif
