// Exercise 1-16
// Readline
// Revise the main routine of the longest line program
// so it will correctly print the length of arbitrarily long
// input lines, and as much as possible of the text.
#include <stdio.h>
#define MAX_SIZE 1000
int readline(char line[], int limit);
int cpy(char from[], char to[]);

int main() {
  char line[MAX_SIZE];  
  char largest[MAX_SIZE];
  int size;
  int max = 0;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    if (size > max) {
      max = size;
      cpy(line, largest);
    }
  }
  if (max > 0) {
    printf("size: %d, content: %s", max, largest);
  }
}

int cpy(char from[], char to[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
  return 0;
}

int readline(char line[], int limit) {
  int c, i;
  for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
    if (i < (limit - 1)) {
      line[i] = c;
    } 
  }
  if (c == '\n') {
    if (i < (limit - 1)) {
      line[i] = c;
    }
    i++;
  }
  if (!i) {
    return 0;
  }
  line[i] = '\0';
  return i;
}
