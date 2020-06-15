#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int players = 0;
  uint8_t spacer = 0;
  uint8_t players_left = 0;
  uint8_t pot = 0;
  uint16_t position = 0;
  int seed = 0;
  uint8_t roll;
  uint8_t numrolls;
  uint8_t counter = 0; // used for counting with a loop
  typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
  faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
  int money[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
  const char *names[] = { "Whoopi", "Dale", "Rosie", "Jimmie", "Barbara",
    "Kyle", "Raven", "Tony", "Jenny", "Clint" };
  printf("Random seed: "); // gets seed from user.
  scanf("%d", &seed);
  srand(seed);
  printf("How many players? "); // gets number of players from user
  scanf("%d", &players);
  players_left = players;
  // Runs a loop playing the game until there is one player left.
  // The if statements check to see if the player is still in the game and how       many rolls they will take.
  while (players_left > 1) {
    players_left = players; // Resets the checker for players left.
    if (money[position] > 0) {
      printf("%s rolls... ", names[position]);
      spacer = 1;
      if (money[position] > 2) {
        numrolls = 3;
      }
      if (money[position] == 2) {
        numrolls = 2;
      }
      if (money[position] == 1) {
        numrolls = 1;
      }
      // This loop simulates the rolls using if statements to see the result of          rolling the die.
      while (numrolls > 0) {
        roll = (rand() % 6);
        if (die[roll] == LEFT) {
          money[position]--;
          position = (position + players - 1) % players;
          printf("gives $1 to %s ", names[position]);
          money[position]++;
          position = (position + 1) % players;
        }
        if (die[roll] == RIGHT) {
          money[position]--;
          position = (position + 1) % players;
          printf("gives $1 to %s ", names[position]);
          money[position]++;
          position = (position + players - 1) % players;
        }
        if (die[roll] == CENTER) {
          money[position] = money[position] - 1;
          pot++;
          printf("puts $1 in the pot ");
        }
        if (die[roll] == PASS) {
          printf("gets a pass ");
        }
        numrolls--;
      }
    }
    // This loop checks how many players are left.
    while (counter < players) {
      if (money[counter] == 0) {
        players_left--;
      }
      counter++;
    }
    counter = 0;
    if (spacer > 0 && players_left > 1) {
      printf("\n");
      spacer = 0;
    }
    position = (position + 1) % players;
  }
  // Prints out the winning player and their balance.
  while (counter < players) {
    if (money[counter] > 0) {
      printf("\n%s wins the $%d pot with $%d left in the bank! \n",
          names[counter], pot, money[counter]);
    }
    counter++;
  }
  return 0;
}
