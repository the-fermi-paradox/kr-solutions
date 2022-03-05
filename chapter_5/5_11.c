/* Exercise 5-11 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define TAB_STOP 8
#define PRINTING_TAB 1
#define NOT_PRINTING_TAB 0
int readline(char* line, int lim);
void prune(char* from, char* to);
void entab(char* from, char* to);
int get_distance(int i);

int stops[MAX_SIZE];
int* stp = stops;

int main(int argc, char* argv[]) {
  char line[MAX_SIZE];
  char pruned[MAX_SIZE];

  ++argv;
  while (argc-- > 1) {
    *stp++ = atoi(*argv++);
  }

  int size;
  while ((size = readline(line, MAX_SIZE) > 0)) {
//    prune(line, pruned);
    entab(line, pruned);
    printf("%s", pruned);
  }
}

void entab(char* from, char* to) {
  int spaces;
  char* forig = from;
  // "iterate over // the string"
  while (*from) {
    // if its not a blank just copy
    if (*from != ' ') {
      *to++ = *from++;
      continue;
    }

    spaces = 0;
    // count the number of spaces
    while (*from == ' ') {
      ++spaces;
      ++from;
    }
    int distance;
    // first fill in as many tabs as we need
    while (spaces >= (distance = get_distance(((from - spaces) - forig)))) {
      *to++ = '\t';
      spaces -= distance;
    }
    // then we fill in the remainder with blanks
    while (spaces > 0) {
      *to++ = '*';
      --spaces;
    }
  }
  *to = '\0';
}

int get_distance(int i) {
  int* stor = stops;
  while (stor < stp && i >= *stor) {
    ++stor;
  }
  return (stor >= stp) ? TAB_STOP - (i % TAB_STOP) : *stor - i;
}

void prune(char* from, char* to) {
  char* torig = to;
  int* stor = stops;
  while (*from) {
    if (*from != '\t') {
      *to++ = *from++;
      continue;
    }

    while (stor < stp && to - torig >= *stor) {
      ++stor;
    }

    do {
      *to++ = '*';
    } while ((stor < stp && (to - torig) < *stor) || (stor >= stp && (to - torig) % TAB_STOP));

    ++from;
  }
  *to = '\0';
}

int readline(char* line, int lim) {
  int c;
  int i = 0;
  while ((c = getchar()) != EOF) {
    if (i < lim - 1) {
      line[i] = c;
    }
    ++i;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  line[i] = '\0';
  return i;
}
