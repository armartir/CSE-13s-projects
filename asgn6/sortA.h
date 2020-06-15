
#ifndef __SORTA_H__
#define __SORTA_H__

#include <inttypes.h>
#include <stdbool.h>

uint64_t moves;
uint64_t compares;

uint32_t min_index(uint32_t a[], uint32_t first, uint32_t last);

void sort_A(uint32_t a[], uint32_t length);

uint64_t moves_A(void);

uint64_t compares_A(void);
#endif
