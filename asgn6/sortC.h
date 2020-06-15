
#ifndef __SORTC_H__
#define __SORTC_H__

#include <inttypes.h>
#include <stdbool.h>

uint64_t moves;
uint64_t compares;

void sort_C(uint32_t a[], uint32_t length);

uint64_t moves_C(void);
uint64_t compares_C(void);

#endif
