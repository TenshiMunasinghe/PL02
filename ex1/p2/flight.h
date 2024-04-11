#pragma once

typedef struct {
  int hour;
  int minute;
} Time;

typedef struct {
  char *id;
  char *location;
  Time time;
} Flight;

