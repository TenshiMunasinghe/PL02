#include "time.h"

int isValidTime(Time time)
{
  if (time.hour >= 0 && time.minute >= 0 && time.minute < 60)
    return 1;
  return 0;
};

float toMinutes(Time time)
{
  return (float)time.hour + ((float)time.minute / 60);
};

float timeDifference(Time time1, Time time2)
{
  return toMinutes(time1) - toMinutes(time2);
};
