
#ifndef __SORTD_H__
#define __SORTD_H__

#include <inttypes.h>
#include <stdbool.h>

uint64_t moves;
uint64_t compares;

void sort_D(uint32_t a[], uint32_t length);

uint64_t moves_D(void);

uint64_t compares_D(void);

#endif
