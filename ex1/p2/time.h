#pragma once

typedef struct
{
  unsigned int hour;
  unsigned int minute;
} Time;

int isValidTime(Time time);
float toMinutes(Time time);
float timeDifference(Time time1, Time time2);