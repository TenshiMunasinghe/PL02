#include <stdio.h>
#include <stdlib.h>

// Complete the project following the Hands-on 1 discussion
// and hints you can find in the source code comments

#include "timing.h"

int main() {
  Time departure;
  TimeSpan journey;

  Time arrival;

  if (requestTime(&departure) != 1)
    return EXIT_FAILURE;

  if (!isTimeValid(departure)) {
    printf("Illegal departure time.\n");
    return EXIT_FAILURE;
  }

  arrival.day = departure.day;
  arrival.hours = departure.hours;
  arrival.minutes = departure.minutes;

  // Print departure time to the console
  // ...
  printf("Departure time ");
  printTime(departure);
  printf("\n");

  // Request and print the journay time (TimeSpan object) in similar manner
  // as in the above code for requesting and printing departure time
  // ...
  requestTimeSpan(&journey);
  printf("Time span ");
  printTimeSpan(journey);
  printf("\n");

  // Compute arrival time for given departure and journey time
  // using  addTimeSpan() function
  // ...
  addTimeSpan(&arrival, journey);

  // Check that the results as printed correctly,
  // then modify this code with using printTime() function
  printf("Arrival time on the day %d - %02d:%02d\n", arrival.day, arrival.hours,
         arrival.minutes);
  return EXIT_SUCCESS;
}
