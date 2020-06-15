#include "sortA.h"
#include "sortB.h"
#include "sortC.h"
#include "sortD.h"
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int c;
  int32_t condition;
  uint32_t count;
  uint8_t choice_a, choice_b, choice_c, choice_d;
  uint32_t seed = 8222022;
  uint32_t capacity = 100;
  uint32_t print = 100;
  while ((c = getopt(argc, argv, "Aabcdp:r:n:")) != -1) {
    if (c == 'A') {
      choice_a = 1;
      choice_b = 1;
      choice_c = 1;
      choice_d = 1;
    }
    if (c == 'a') {
      choice_a = 1;
    }
    if (c == 'b') {
      choice_b = 1;
    }
    if (c == 'c') {
      choice_c = 1;
    }
    if (c == 'd') {
      choice_d = 1;
    }
    if (c == 'p') {
      condition = atoi(optarg);
      if (condition < 0) {
        printf("error negative arguement \n");
        return 0;
      }
      print = condition;
    }
    if (c == 'r') {
      condition = atoi(optarg);
      if (condition < 0) {
        printf("error negative arguement \n");
        return 0;
      }
      seed = condition;
    }
    if (c == 'n') {
      condition = atoi(optarg);
      if (condition < 0) {
        printf("error negative arguement \n");
        return 0;
      }
      capacity = condition;
    }
  }
  srand(seed);
  uint32_t *array_main = (uint32_t *)calloc(capacity, sizeof(uint32_t));
  for (uint32_t i = 0; i < capacity; i++) {
    array_main[i] = (rand() & 0x00ffffff);
    //printf("position %d number %d \n", i, array_main[i]);
  }
  if (choice_a == 1) {
    printf("Sort A \n");
    //creates copy of array
    uint32_t *array_a = (uint32_t *)calloc(capacity, sizeof(uint32_t));
    for (uint32_t i = 0; i < capacity; i++) {
      array_a[i] = array_main[i];
    }

    sort_A(array_a, capacity);
    printf("%d elements \n", capacity);
    printf("%" PRIu64 " moves \n", moves_A());
    printf("%" PRIu64 " compares \n", compares_A());
    //prints array
    count = 0;
    while (count < print && count < capacity) {
      printf("    %8.0d", array_a[count]);
      count++;
      if ((count % 7) == 0) {
        printf("\n");
      }
    }
    printf("\n");
    //deletes array
    free(array_a);
    array_a = NULL;
  }
  if (choice_b == 1) {
    printf("Sort B \n");
    uint32_t *array_b = (uint32_t *)calloc(capacity, sizeof(uint32_t));
    for (uint32_t i = 0; i < capacity; i++) {
      array_b[i] = array_main[i];
    }

    sort_B(array_b, capacity);
    printf("%d elements \n", capacity);
    printf("%" PRIu64 " moves \n", moves_B());
    printf("%" PRIu64 " compares \n", compares_B());
    //printfs array
    count = 0;
    while (count < print && count < capacity) {
      printf("    %8.0d", array_b[count]);
      count++;
      if ((count % 7) == 0) {
        printf("\n");
      }
    }
    printf("\n");
    //deletes array
    free(array_b);
    array_b = NULL;
  }
  if (choice_c == 1) {
    printf("Sort C \n");
    uint32_t *array_c = (uint32_t *)calloc(capacity, sizeof(uint32_t));
    for (uint32_t i = 0; i < capacity; i++) {
      array_c[i] = array_main[i];
    }
    //sends the array through the sorting algorithm
    sort_C(array_c, capacity);
    printf("%d elements \n", capacity);
    printf("%" PRIu64 " moves \n", moves_C());
    printf("%" PRIu64 " compares \n", compares_C());
    count = 0;
    while (count < print && count < capacity) {
      printf("    %8.0d", array_c[count]);
      count++;
      if ((count % 7) == 0) {
        printf("\n");
      }
    }
    printf("\n");
    // deletes array
    free(array_c);
    array_c = NULL;
  }
  if (choice_d == 1) {
    printf("Sort D \n");
    uint32_t *array_d = (uint32_t *)calloc(capacity, sizeof(uint32_t));
    for (uint32_t i = 0; i < capacity; i++) {
      array_d[i] = array_main[i];
    }
    //sends array through sorting algorithm
    sort_D(array_d, capacity);
    printf("%d elements \n", capacity);
    printf("%" PRIu64 " moves \n", moves_D());
    printf("%" PRIu64 " compares \n", compares_D());
    count = 0;
    while (count < print && count < capacity) {
      printf("    %8.0d", array_d[count]);
      count++;
      if ((count % 7) == 0) {
        printf("\n");
      }
    }
    printf("\n");
    // deletes array
    free(array_d);
    array_d = NULL;
  }
  free(array_main);
  array_main = NULL;
  return 0;
}
