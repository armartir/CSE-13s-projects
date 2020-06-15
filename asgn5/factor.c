#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  uint32_t cap = 100000;
  int choice; //user argument therefor using int is easier
  uint32_t primis;
  uint32_t remainder = 0;

  while ((choice = getopt(argc, argv, "-n:")) != -1) { // Takes user argument
    if (choice == 'n') {
      cap = atoi(optarg);
    }
  }
  BitVector *p = bv_create(cap);
  sieve(p);
  for (uint32_t i = 2; i <= cap; i++) {
    printf("%d ", i);
    primis = 2;
    // I ended up checking if its composite or prime with a loop-
    // because I put that into my design doc and later realised
    // that the bitvector does the exact same thing
    if (bv_get_bit(p, i) == 1) {
      primis = 1;
    }
    //actual bit vector implementation
    if (primis == 2) {
      printf("C:");
      remainder = i;
      for (uint32_t bitpost = 2; bitpost < i; bitpost++) {
        if (bv_get_bit(p, bitpost)) {
          while ((remainder % bitpost) == 0) {
            remainder = remainder / bitpost;
            printf(" %d", bitpost);
          }
        }
        if (remainder == 1) {
          break;
        }
      }
    }
    if (primis == 1) {
      printf("P");
    }
    printf("\n");
  }
  bv_delete(p);
  return 0;
}
