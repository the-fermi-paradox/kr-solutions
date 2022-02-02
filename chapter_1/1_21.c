// Exercise 1-21
// ENTAB
// Write a program entab that replaces strings of blanks
// by the minimum number of tabs and blanks to achieve
// the same spacing. Use the same tab stops as for detab.
// When either a tab or a single blank would suffice to
// reach a tab stop, which should be given preference?
#include <stdio.h>

#define MAX_SIZE 1000
#define TAB_STOP 8
int readline(char line[], int lim);
void entab(char from[], char to[]);
int get_distance(int i);

int main() {
  int size;
  char line[MAX_SIZE];
  char output[MAX_SIZE];
  while ((size = readline(line, MAX_SIZE)) > 0) {
    entab(line, output);
    printf("%s", output);
  }
}
void entab(char from[], char to[]) {
  int i = 0;
  int j = 0;
  int spaces;
  // "iterate over // the string"
  while (from[i] != '\0') {
    // if its not a blank just copy
    if (from[i] != ' ') {
      to[j] = from[i];
      ++i;
      ++j;
    } else {
      spaces = 0;
      // count the number of spaces
      while (from[i + spaces] == ' ') {
        ++spaces;
      }
      int distance;
      // first fill in as many tabs as we need
      while (spaces > (distance = get_distance(i))) {
        to[j] = '\t';
        spaces -= distance;
        i += distance;
        ++j;
      }
      // then we fill in the remainder with blanks
      while (spaces > 0) {
        to[j] = '*';
        --spaces;
        ++j;
        ++i;
      }
    }
  }
  to[j] = '\0';
}

int get_distance(int i) {
  return TAB_STOP - (i % TAB_STOP);
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
