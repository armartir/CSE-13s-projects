
#ifndef __SORTB_H__
#define __SORTB_H__

#include <inttypes.h>
#include <stdbool.h>

uint64_t moves;
uint64_t compares;

void sort_B(uint32_t a[], uint32_t length);

uint64_t moves_B(void);
uint64_t compares_B(void);

#endif
