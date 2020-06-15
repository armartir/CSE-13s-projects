
#include "sortD.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//I am sourcing the pseudocode for Darrel Long 
void sort_D(uint32_t a[], uint32_t length) {
  uint32_t gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
  uint32_t n = length;
  uint32_t temp;
  uint32_t j;
  moves = 0;
  compares = 0;
  moves += 1;
  compares += 1;
  for (uint32_t z = 0; z < 8; z++) {

    for (uint32_t i = gaps[z]; i < n; i += 1) {
      temp = a[i];
      moves += 1;
      for (j = i; j >= gaps[z] && a[j - gaps[z]] > temp; j -= gaps[z]) {
        compares += 1;
        a[j] = a[j - gaps[z]];
        moves += 1;
      }
      compares += 1;
      a[j] = temp;
      moves += 1;
    }
  }
}

uint64_t moves_D(void) {
  return moves;
}

uint64_t compares_D(void) {
  return compares;
}
