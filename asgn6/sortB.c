
#include "sortB.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y)                                                             \
  {                                                                            \
    uint32_t t = x;                                                            \
    x = y;                                                                     \
    y = t;                                                                     \
    moves += 3;                                                                \
  }

//I am sourcing the pseudo code from Darrall Long
void sort_B(uint32_t a[], uint32_t length) {
  uint32_t n = length;
  bool swapped;
  moves = 0;
  compares = 0;
  do {
    swapped = false;
    for (uint32_t i = 1; i <= (n - 1); i++) {
      compares += 1;
      if (a[i - 1] > a[i]) {
        SWAP(a[i - 1], a[i]);
        swapped = true;
      }
    }
    n = n - 1;
  } while (swapped);
}

uint64_t moves_B(void) {
  return moves;
}

uint64_t compares_B(void) {
  return compares;
}
