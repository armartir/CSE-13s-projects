#include <stdio.h>

int main(void) {
  printf("Celsius   Kelvin   Fahrenheit   Rakine   Delisle   Reaumur   Romer "
         "\n"); //creating the basic headers
  printf("-------   ------   ----------   ------   -------   -------   ----- "
         "\n"); // Added dashes
  float celsius = 0; //creates all of the variables
  float kelvin = 0;
  float fahrenheit = 0;
  float rankine = 0;
  float delisle = 0;
  float reaumur = 0;
  float romer = 0;
  float max = 200;
  while (
      celsius < max) { // made a while loop which goes from zero to 200 degrees
    kelvin = celsius + 273.15; // logic for converting celsius to kelvin
    fahrenheit = ((9 * celsius) / 5)
                 + 32; // logic for converting celsius to fahrenheit
    rankine = ((9 * celsius) / 5)
              + 491.672; // logic for converting celsius to rankine
    delisle
        = 3 * (100 - celsius) / 2; // logic for converting celsius to delisle
    reaumur = ((4 * celsius) / 5); // logic for converting celsius to reaumur
    romer
        = ((21 * celsius) / 40) + 7.5; // logic for converting celsius to romer
    printf(" %6.2f   %6.2f  %11.2f  %7.2f   %7.2f %9.2f %7.2f\n", celsius,
        kelvin, fahrenheit, rankine, delisle, reaumur, romer);
    celsius = celsius + 10; // incriments up 10 degrees at a time(in celsius)
  }

  return 0;
}
