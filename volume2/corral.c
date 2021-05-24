// Corral
// Basic-Computer-Spiele Band 2
// Sybex Verlag
// Converted to C by Michael Stroucken
// Original by Colin Keay

// cc -o corral corral.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int p[] = {0, 1, 2, 3, 3, 2, 2, 1, 0, -1};
const int q[] = {1, 2, 3, 4, 5, 4, 3, 2, 1, 0};

#define ARENASIZE 21

void tab(int num) {
  int i;
  for (i=0; i<num; i++) {
    printf(" ");
  }
  return;
}

int fnr(unsigned int p) {
  return arc4random_uniform(p);
}

void getRandomState(int *randomVal, int *pVal, int *qVal) {
  *randomVal = fnr(10);
  *pVal = p[*randomVal];
  *qVal = q[*randomVal];
}

void boundHorse(int *horsePos) {
  if (*horsePos < 0) *horsePos = 0;
  if (*horsePos > ARENASIZE - 1) *horsePos = ARENASIZE - 1;
}

void setupArena(char* arena, int cowboyPos, int horsePos) {
  memset(arena, ' ', ARENASIZE);
  if (cowboyPos == horsePos) {
    arena[cowboyPos] = '#';
  } else {
    arena[cowboyPos] = 'C';
    arena[horsePos] = 'H';
  }
}

void game() {
  char arena[ARENASIZE+1];
  arena[ARENASIZE] = 0;
  int cowboyPos = 0; // starts at left edge
  int cowboyLeftOfHorse = 1;
  int kickFlight = 0;
  int moveCount = 0;
  int kickCount = 0;
  int horsePos, randomVal, pVal, qVal, cowboyHitpoints;
  char *action;
  getRandomState(&randomVal, &pVal, &qVal);

  if (randomVal > 5) {
    qVal = -qVal;
  }

  horsePos = 13 + qVal;
  boundHorse(&horsePos);

  cowboyHitpoints = 2 + pVal;
  printf("\n");

  action = "            ";
  while (1) {
    setupArena(arena, cowboyPos, horsePos);
    printf("%d\tI%sI\t%s", moveCount, arena, action);
    int distance = horsePos - cowboyPos;
    cowboyLeftOfHorse = (distance > 0) ? 1 : -1;
    distance = abs(distance);

    moveCount++;
    if (kickFlight > 0) {
      if (kickCount > cowboyHitpoints) {
        printf("\n");
        printf("Those kicks landed you in the hospital!\n");
        printf(" Get well soon!!\n");
        return;
      }

      kickFlight--;
      printf("\n");
      getRandomState(&randomVal, &pVal, &qVal);
      horsePos = horsePos + cowboyLeftOfHorse * (pVal + 1);
      boundHorse(&horsePos);
      action = "            ";
      continue;
    }

    if (moveCount > 100) {
      printf("\n");
      printf("Enough!! You'd do better as camp cook!\n");
      return;
    }

    int moveInput;
    int inputOk = 0;
    while (!inputOk) {
      char *line = NULL;
      size_t linecap = 0;
      printf("? ");
      getline(&line, &linecap, stdin);
      moveInput = atoi(line);
      free(line);

      if (moveInput > 0 && moveInput < 6) {
        int cowboyTarget = cowboyPos + cowboyLeftOfHorse * moveInput;
        if (cowboyTarget > 0 && cowboyTarget < ARENASIZE) {
          inputOk = 1;
          cowboyPos = cowboyTarget;
        }
      }

      if (!inputOk) {
        printf("Illegal move. Try again\t");
      }
    }

    getRandomState(&randomVal, &pVal, &qVal);
    horsePos = horsePos + cowboyLeftOfHorse * pVal;
    boundHorse(&horsePos);

    if (distance < 2 * moveInput && distance > 1) {
      goto bolt;
    }

    if (randomVal > 2 || (horsePos > 0 && horsePos < ARENASIZE - 1)) {
      if (abs(horsePos - cowboyPos) > 2) {
        action = "            ";
        continue;
      }
      getRandomState(&randomVal, &pVal, &qVal);
      if (randomVal > 3) {
        if (horsePos == cowboyPos) {
          setupArena(arena, cowboyPos, horsePos);
          printf("\tI%sI\n", arena);
          printf("\n");
          printf("Yippee!!  Now see if you can catch him in fewer moves\n");
          return;
        }
        action = "            ";
        continue;
      }
      getRandomState(&randomVal, &pVal, &qVal);
      kickFlight = pVal + 2;
      kickCount++;
      horsePos = horsePos - 5 * cowboyLeftOfHorse;
      boundHorse(&horsePos);
      action = "kicked";
      continue;
    }
    if (distance > 7) {
      action = "            ";
      continue;
    }
   
    bolt: { 
      int boltStrength = 9 + 2 * pVal;
      horsePos = horsePos - cowboyLeftOfHorse * boltStrength;
      boundHorse(&horsePos);
      if (abs(horsePos - cowboyPos) > 1) {
      } else {
        horsePos = horsePos - 3 * cowboyLeftOfHorse;
      }
      action = "bolted      ";
      continue; 
    }
  }    

}

int main() {
  char *line = NULL;
  size_t linecap = 0;

  tab(26);printf("Corral\n");
  tab(20);printf("Creative Computing\n");
  tab(18);printf("Morristown, New Jersey\n");
  printf("\n\n\n");
  printf("  You are the cowboy. Go catch your horse in the corral!\n");
  printf("Do you want full instructions? ");

  int compare=0;
  line = NULL;
  linecap = 0;
  getline(&line, &linecap, stdin);
  compare = strncasecmp(line, "n", 1);
  free(line);

  if (compare) {
    printf("You move toward your horse 1 to 5 steps at a time.\n");
    printf("If you move more than half the separation, he will bolt!\n");
    printf("He may also bolt when he is close to the rail.\n");
    printf("When you come within 2 steps, he may kick. So look out!!\n");
    printf("\n");
    printf("After '?' type in digit from 1 to 5 for cowboy's next move\n");
  }

  compare = 0;
  do {
    game();
    printf("Another roundup? ");
    line = NULL;
    linecap = 0;
    getline(&line, &linecap, stdin);
    compare = strncasecmp(line, "y", 1);
    free(line);
  } while (!compare);

  return 0;
}
