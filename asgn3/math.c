#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

long double Sin(long double msin);
long double Cos(long double mcos);
long double Tan(long double mtan);
long double Exp(long double mexp);

//variables for printing segment
long double max, increment, cap, library, calcfunc, difference;

//variables for different functions
long double square, num, den, sum;

int main(int argc, char **argv) {
  int choice;

  while ((choice = getopt(argc, argv, "sctea")) != -1) {
    if (choice == 's' || choice == 'a') {
      max = M_PI * 2;
      increment = M_PI / 16;
      cap = max * -1;
      printf("x        Sin             Library         Difference\n");
      printf("-        ---             -------         ----------\n");
      while (cap < max) {
        calcfunc = Sin(cap);
        library = sinl(cap);
        difference = calcfunc - library;
        printf("%7.4Lf %11.8LF     %11.8Lf %17.10Lf\n", cap, calcfunc, library,
            difference);
        cap = cap + increment;
      }
    }
    if (choice == 'c' || choice == 'a') {
      max = M_PI * 2;
      increment = M_PI / 16;
      cap = max * -1;
      printf("x        Cos             Library         Difference\n");
      printf("-        ---             -------         ----------\n");
      while (cap < max) {
        calcfunc = Cos(cap);
        library = cosl(cap);
        difference = calcfunc - library;
        printf("%7.4Lf %11.8LF     %11.8Lf %17.10Lf\n", cap, calcfunc, library,
            difference);
        cap = cap + increment;
      }
    }
    if (choice == 't' || choice == 'a') {
      max = M_PI / 2;
      max = max - .001;
      increment = M_PI / 16;
      cap = max * -1;
      printf("x        Tan             Library         Difference\n");
      printf("-        ---             -------         ----------\n");
      calcfunc = Tan(cap);
      library = tanl(cap);
      difference = calcfunc - library;
      //needed to print this seperately to prevent spacing error
      printf("%7.4Lf %11.8LF   %9.8Lf  %14.10Lf\n", cap, calcfunc, library,
          difference);
      cap = cap + increment;
      while (cap < max) {
        calcfunc = Tan(cap);
        library = tanl(cap);
        difference = calcfunc - library;
        printf("%7.4Lf %11.8LF     %11.8Lf %17.10Lf\n", cap, calcfunc, library,
            difference);
        cap = cap + increment;
      }
    }
    if (choice == 'e' || choice == 'a') {
      max = 10;
      increment = .1;
      cap = 0;
      printf("x        Exp             Library         Difference\n");
      printf("-        ---             -------         ----------\n");
      while (cap < max) {
        calcfunc = Exp(cap);
        library = expl(cap);
        difference = calcfunc - library;
        printf("%7.4Lf  %5.8Lf %15.8Lf	%13.10Lf  \n", cap, calcfunc, library,
            difference);
        cap = cap + increment;
      }
    }
  }
  return 0;
}
//logic for sine
long double Sin(long double msin) {
  square = msin * msin;
  num = 4469552712 * square;
  num = 538531796880 - num;
  num = num * square;
  num = num - 17478564143040;
  num = num * square;
  num = num + 124345562140800;
  num = msin * num;
  den = 1768969 * square;
  den = den + 366075360;
  den = den * square;
  den = den + 43268148000;
  den = den * square;
  den = den + 3245696213760;
  den = den * square;
  den = den + 124345562140800;
  sum = num / den;
  return sum;
}
//logic for cosine
long double Cos(long double mcos) {
  square = mcos * mcos;
  num = 24694099 * square;
  num = num - 5773801680;
  num = num * square;
  num = num + 344048221440;
  num = num * square;
  num = num - 5595410620800;
  num = num * square;
  num = num + 11797350364800;
  den = 209794 * square;
  den = den + 37502280;
  den = den * square;
  den = den + 4124237040;
  den = den * square;
  den = den + 303264561600;
  den = den * square;
  den = den + 11797350364800;
  sum = num / den;
  return sum;
}
//logic for tan
long double Tan(long double mtan) {
  square = mtan * mtan;
  num = 55 * square;
  num = 25740 - num;
  num = num * square;
  num = num - 2837835;
  num = num * square;
  num = num + 91891800;
  num = num * square;
  num = num - 654729075;
  num = num * mtan;
  den = square - 1485;
  den = den * square;
  den = den + 315315;
  den = den * square;
  den = den - 18918900;
  den = den * square;
  den = den + 310134825;
  den = den * square;
  den = den - 654729075;
  sum = num / den;
  return sum;
}
//logic fo e^x
long double Exp(long double mexp) {
  int counter = 1;
  long double counterden;
  num = 1.00;
  den = 1.00;
  sum = 1.00;
  counterden = den - 1;
  while (counter < 100) {
    num = num * mexp;
    while (counterden > 0) {
      den = den * counterden;
      counterden = counterden - 1;
    }
    sum = sum + (num / den);
    counter++;
    den = counter;
    counterden = den - 1;
  }
  return sum;
}
