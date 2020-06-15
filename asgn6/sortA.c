#include "sortA.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y)                                                             \
  {                                                                            \
    uint32_t t = x;                                                            \
    x = y;                                                                     \
    y = t;                                                                     \
    moves += 3;                                                                \
  }

//I am sourcing this code from Darrell Long
uint32_t min_index(uint32_t a[], uint32_t first, uint32_t last) {
  uint32_t smallest = first;
  for (uint32_t i = first; i < last; i += 1) {
    smallest = a[i] < a[smallest] ? i : smallest;
    compares += 1;
  }
  return smallest;
}

void sort_A(uint32_t a[], uint32_t length) {
  compares = 0;
  moves = 0;
  for (uint32_t i = 0; i < length - 1; i += 1) {
    uint32_t smallest = min_index(a, i, length);
    if (smallest != i) {
      SWAP(a[smallest], a[i]);
    }
  }
  return;
}

uint64_t moves_A(void) {
  return moves;
}

uint64_t compares_A(void) {
  return compares;
}
