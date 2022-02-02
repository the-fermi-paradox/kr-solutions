// Exercise 1_20
// DETAB
// Write a program detab that replaces tabs
// in the input with the proper number of blanks
// to space to the next tab stop.
// Assume a fixed set of tab stops, 
// say every n columns. Should n be a variable
// or a symbolic parameter?

#include <stdio.h>
#define MAX_SIZE 1000
#define TAB_STOP 8
#define PRINTING_TAB 1
#define NOT_PRINTING_TAB 0
int readline(char line[], int lim);
void prune(char from[], char to[]);
int countchar(char from[], char c);

int main() {
  char line[MAX_SIZE];
  char pruned[MAX_SIZE];
  int size;
  while ((size = readline(line, MAX_SIZE) > 0)) {
    prune(line, pruned);
    printf("%s", pruned);
  }
}

void prune(char from[], char to[]) {
  int i = 0;
  int k = 0;
  int multiplier = 1;
  while (from[i] != '\0') {
    if (from[i] == '\t') {
      for (; k <= (multiplier * TAB_STOP) - 1; k++) {
        to[k] = '*';
      }
    } else {
      to[k] = from[i];
      ++k;
    }
    if (k > (multiplier * TAB_STOP) - 1) {
      ++multiplier;
    }
    ++i;
  }
  to[k] = '\0';
}

int readline(char line[], int lim) {
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
