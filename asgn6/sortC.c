#include "sortC.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//I am sourcing the pseudo code from Darrell Long
void sort_C(uint32_t a[], uint32_t length) {
  uint32_t n = length;
  uint32_t tmp;
  int32_t j;
  moves = 0;
  compares = 0;
  for (uint32_t i = 0; i < n; i++) {
    tmp = a[i];
    moves += 1;
    j = i - 1;
    while (j >= 0 && a[j] > tmp) {
      compares += 1;
      a[j + 1] = a[j];
      moves += 1;
      j = j - 1;
    }
    compares += 1;
    a[j + 1] = tmp;
    moves += 1;
  }
}

uint64_t moves_C(void) {
  return moves;
}

uint64_t compares_C(void) {
  return compares;
}
