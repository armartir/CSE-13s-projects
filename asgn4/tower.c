#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// used arrays for peg representation
void recursion(int pega[], int pegb[], int pegc[]);
int rings = 5;
int choice;
int typer = 0; // decides if recursion will be used
int types = 0; // decides if stack type will be used
long double moves = 0.00;
const char *pegs[] = { "A", "B", "C" };
int pega, pegb, pegc, ringa, ringb, ringc, spega, spegb, spegc;
int evenoneloc, oddoneloc;

int main(int argc, char **argv) {
  while ((choice = getopt(argc, argv, "sr-n:")) != -1) { // Takes user argument
    if (choice == 's') {
      types = 1;
    }
    if (choice == 'r') {
      typer = 1;
    }
    if (choice == 'n') {
      rings = atoi(optarg);
    }
  }
  Stack *a = stack_create(rings + 10, 'a'); // one stack for each peg
  Stack *b = stack_create(rings + 10, 'b');
  Stack *c = stack_create(rings + 10, 'c');
  if (types == 1) {
    moves = 0;
    printf("\n===============================\n");
    printf("----------   STACKS   ---------\n");
    printf("===============================\n");
    ringa = rings;
    ringb = 0;
    ringc = 0;
    oddoneloc = 5;
    evenoneloc = 5;
    for (int i = 0; i < rings; i++) { // pushes all values onto peg a
      stack_push(a, rings - i);
    }
    if ((rings % 2) == 1) {
      oddoneloc = 0;
    }
    if ((rings % 2) == 0) {
      evenoneloc = 0;
    }
    // Main stack function doing simulation
    while (ringb < rings) {
      if (rings == 1) {
        printf("Move ring 1 from peg A to peg B\n");
        printf("Number of moves: 1\n");
        break;
      }
      if (rings == 2) {
        printf("Move ring 1 from peg A to peg C\n");
        printf("Move ring 2 from peg A to peg B\n");
        printf("Move ring 1 from peg C to peg B\n");
        printf("\nNumber of moves: 3\n\n");
        break;
      }
      if (oddoneloc == 0 || evenoneloc == 2) { // moves ring one to peg b
        if (oddoneloc == 0) {
          spega = stack_pop(a);
          stack_push(b, spega);
          ringb++;
          if (ringa > 0) {
            ringa--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spega, pegs[0], pegs[1]);
          moves++;
        }
        if (evenoneloc == 2) {
          spegc = stack_pop(c);
          stack_push(b, spegc);
          ringb++;
          if (ringc > 0) {
            ringc--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegc, pegs[2], pegs[1]);
          moves++;
        }
        if (ringb == (rings)) { // breaking condition
          printf("\nNumber of moves: %.0Lf\n\n", moves);
          break;
        }
        if (stack_empty(a)) { // stack_empty(a)(had issues possibly in if format)
          spega = -1;
        } else {
          spega = stack_pop(a);
        }
        if (ringc == 0) { // stack_empty(c)(had issues possibly in if format)
          spegc = -1;
        } else {
          spegc = stack_pop(c);
        }
        // checking to see which ring is moved from the other two pegs
        if (((spega < spegc) || ringc == 0) && ringa != 0) {
          if (spegc > 0) {
            stack_push(c, spegc);
          }
          if (spega > 0) {
            stack_push(c, spega);
            ringc++;
          }
          if (ringa > 0) {
            ringa--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spega, pegs[0], pegs[2]);
          moves++;
        } else {
          if (spega > 0) {
            stack_push(a, spega);
          }
          if (spegc > 0) {
            stack_push(a, spegc);
            ringa++;
          }
          if (ringc > 0) {
            ringc--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegc, pegs[2], pegs[0]);
          moves++;
        }
      }
      if (oddoneloc == 1 || evenoneloc == 0) { // moving ring one to ring c
        if (oddoneloc == 1) {
          spegb = stack_pop(b);
          stack_push(c, spegb);
          ringc++;
          if (ringb > 0) {
            ringb--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegb, pegs[1], pegs[2]);
          moves++;
        }
        if (evenoneloc == 0) {
          spega = stack_pop(a);
          stack_push(c, spega);
          ringc++;
          if (ringa > 0) {
            ringa--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spega, pegs[0], pegs[2]);
          moves++;
        }
        if (ringa == 0) { // stack_empty(a) same issue as above
          spega = -1;
        } else {
          spega = stack_pop(a);
        }
        if (ringb == 0) { // stack_empty(b) same issue as above
          spegb = -1;
        } else {
          spegb = stack_pop(b);
        }
        if (((spega < spegb) || ringb == 0) && ringa != 0) {
          if (spegb > 0) {
            stack_push(b, spegb);
          }
          if (spega > 0) {
            stack_push(b, spega);
            ringb++;
          }
          if (ringa > 0) {
            ringa--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spega, pegs[0], pegs[1]);
          moves++;
        } else {
          if (spega > 0) {
            stack_push(a, spega);
          }
          if (spegb > 0) {
            stack_push(a, spegb);
            ringa++;
          }
          if (ringb > 0) {
            ringb--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegb, pegs[1], pegs[0]);
          moves++;
        }
      }
      if (oddoneloc == 2 || evenoneloc == 1) { // moving ring one to peg a
        if (oddoneloc == 2) {
          spegc = stack_pop(c);
          stack_push(a, spegc);
          ringa++;
          if (ringc > 0) {
            ringc--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegc, pegs[2], pegs[0]);
          moves++;
        }
        if (evenoneloc == 1) {
          spegb = stack_pop(b);
          stack_push(a, spegb);
          ringa++;
          if (ringb > 0) {
            ringb--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegb, pegs[1], pegs[0]);
          moves++;
        }
        if (ringb == 0) { // stack_empty(b)
          spegb = -1;
        } else {
          spegb = stack_pop(b);
        }
        if (ringc == 0) { // stack_empty(c)
          spegc = -1;
        } else {
          spegc = stack_pop(c);
        }
        if (((spegb < spegc) || ringc == 0) && ringb != 0) {
          if (spegc > 0) {
            stack_push(c, spegc);
          }
          if (spegb > 0) {
            stack_push(c, spegb);
            ringc++;
          }
          if (ringb > 0) {
            ringb--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegb, pegs[1], pegs[2]);
          moves++;
        } else {
          if (spegb > 0) {
            stack_push(b, spegb);
          }
          if (spegc > 0) {
            stack_push(b, spegc);
            ringb++;
          }
          if (ringc > 0) {
            ringc--;
          }
          printf(
              "Move disk %d from peg %s to peg %s\n", spegc, pegs[2], pegs[1]);
          moves++;
        }
      }
      // if even move to the right
      if (evenoneloc == 5) {
        oddoneloc = (oddoneloc + 1) % 3;
      }
      // if odd move to right
      if (oddoneloc == 5) {
        evenoneloc = (evenoneloc + 2) % 3;
      }
    }
  }
  //deletes stacks created to prevent memory leaks
  stack_delete(a);
  stack_delete(b);
  stack_delete(c);
  if (typer == 1) {
    ringa = rings - 1;
    ringb = 0;
    ringc = 0;
    oddoneloc = 5;
    evenoneloc = 5;
    moves = 0;
    printf("\n===============================\n");
    printf("--------   RECURSION   --------\n");
    printf("===============================\n");
    int pegone[rings];
    int pegtwo[rings];
    int pegthree[rings];
    for (int i = 0; i < rings; i++) {
      pegone[i] = rings - i;
      pegtwo[i] = 0;
      pegthree[i] = 0;
    }
    if ((rings % 2) == 1) {
      oddoneloc = 0;
      recursion(pegone, pegtwo, pegthree);
    }
    if ((rings % 2) == 0) {
      evenoneloc = 0;
      recursion(pegone, pegtwo, pegthree);
    }
  }
}
// This function runs the recursion aspect arrays are inputed to represent
// each peg and it prints out moves logic exactly the same as stack part
void recursion(int pega[], int pegb[], int pegc[]) {
  //have issues with 1 ring and 2 rings to this fixes issue
  if (rings == 1) {
    printf("Move ring 1 from peg A to peg B\n");
    printf("Number of moves: 1\n");
    return;
  }
  if (rings == 2) {
    printf("Move ring 1 from peg A to peg C\n");
    printf("Move ring 2 from peg A to peg B\n");
    printf("Move ring 1 from peg C to peg B\n");
    printf("\nNumber of moves: 3\n\n");
    return;
  }
  if (oddoneloc == 0 || evenoneloc == 2) {
    if (oddoneloc == 0) {
      if (pegb[ringb] > 0) {
        ringb++;
      }
      pegb[ringb] = pega[ringa];
      pega[ringa] = 0;
      if (ringa > 0) {
        ringa--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegb[ringb], pegs[0],
          pegs[1]);
      moves++;
    }
    if (evenoneloc == 2) {
      if (pegb[ringb] > 0) {
        ringb++;
      }
      pegb[ringb] = pegc[ringc];
      pegc[ringc] = 0;
      if (ringc > 0) {
        ringc--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegb[ringb], pegs[2],
          pegs[1]);
      moves++;
    }
    if (ringb == (rings - 1)) {
      printf("\nNumber of moves: %.0Lf\n\n", moves);
      return;
    }

    if (((pega[ringa] < pegc[ringc]) || pegc[ringc] == 0) && pega[ringa] != 0) {
      if (pegc[ringc] > 0) {
        ringc++;
      }
      pegc[ringc] = pega[ringa];
      pega[ringa] = 0;
      if (ringa > 0) {
        ringa--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegc[ringc], pegs[0],
          pegs[2]);
      moves++;
    } else {
      if (pega[ringa] > 0) {
        ringa++;
      }
      pega[ringa] = pegc[ringc];
      pegc[ringc] = 0;
      if (ringc > 0) {
        ringc--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pega[ringa], pegs[2],
          pegs[0]);
      moves++;
    }
  }
  if (oddoneloc == 1 || evenoneloc == 0) {
    if (oddoneloc == 1) {
      if (pegc[ringc] > 0) {
        ringc++;
      }
      pegc[ringc] = pegb[ringb];
      pegb[ringb] = 0;
      if (ringb > 0) {
        ringb--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegc[ringc], pegs[1],
          pegs[2]);
      moves++;
    }
    if (evenoneloc == 0) {
      if (pegc[ringc] > 0) {
        ringc++;
      }
      pegc[ringc] = pega[ringa];
      pega[ringa] = 0;
      if (ringa > 0) {
        ringa--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegc[ringc], pegs[0],
          pegs[2]);
      moves++;
    }
    if (((pega[ringa] < pegb[ringb]) || pegb[ringb] == 0) && pega[ringa] != 0) {
      if (pegb[ringb] > 0) {
        ringb++;
      }
      pegb[ringb] = pega[ringa];
      pega[ringa] = 0;
      if (ringa > 0) {
        ringa--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegb[ringb], pegs[0],
          pegs[1]);
      moves++;
    } else {
      if (pega[ringa] > 0) {
        ringa++;
      }
      pega[ringa] = pegb[ringb];
      pegb[ringb] = 0;
      if (ringb > 0) {
        ringb--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pega[ringa], pegs[1],
          pegs[0]);
      moves++;
    }
  }
  if (oddoneloc == 2 || evenoneloc == 1) {
    if (oddoneloc == 2) {
      if (pega[ringa] > 0) {
        ringa++;
      }
      pega[ringa] = pegc[ringc];
      pegc[ringc] = 0;
      if (ringc > 0) {
        ringc--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pega[ringa], pegs[2],
          pegs[0]);
      moves++;
    }
    if (evenoneloc == 1) {
      if (pega[ringa] > 0) {
        ringa++;
      }
      pega[ringa] = pegb[ringb];
      pegb[ringb] = 0;
      if (ringb > 0) {
        ringb--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pega[ringa], pegs[1],
          pegs[0]);
      moves++;
    }

    if (((pegb[ringb] < pegc[ringc]) || pegc[ringc] == 0) && pegb[ringb] != 0) {
      if (pegc[ringc] > 0) {
        ringc++;
      }
      pegc[ringc] = pegb[ringb];
      pegb[ringb] = 0;
      if (ringb > 0) {
        ringb--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegc[ringc], pegs[1],
          pegs[2]);
      moves++;
    } else {
      if (pegb[ringb] > 0) {
        ringb++;
      }
      pegb[ringb] = pegc[ringc];
      pegc[ringc] = 0;
      if (ringc > 0) {
        ringc--;
      }
      printf("Move disk %d from peg %s to peg %s\n", pegb[ringb], pegs[2],
          pegs[1]);
      moves++;
    }
  }
  if (evenoneloc == 5) {
    oddoneloc = (oddoneloc + 1) % 3;
  }
  if (oddoneloc == 5) {
    evenoneloc = (evenoneloc + 2) % 3;
  }
  recursion(pega, pegb, pegc);
}
