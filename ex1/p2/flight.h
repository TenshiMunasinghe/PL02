#pragma once

typedef struct {
  int hour;
  int minute;
} Time;

typedef struct {
  char id[10];
  char location[30];
  Time *time;
} Flight;
