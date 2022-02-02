// Exercise 1-18
// Trim
// Write a program to remove trailing blanks and tabs
// from each line of input, and to delete entirely blank lines.
#include <stdio.h>
#define MAX_SIZE 1000
#define IN_TRAILING_SPACE 0
#define OUT_TRAILING_SPACE 1

int readline(char line[], int limit);

int main() {
  char line[MAX_SIZE];  
  int size;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    printf("%s", line);
  }
}

int readline(char line[], int limit) {
  int c, i;
  int state = IN_TRAILING_SPACE;
  i = 0;
  while ((c = getchar()) != EOF && c != '\n') {
    if ((c != ' ' && c != '\t' && state == IN_TRAILING_SPACE) || state == OUT_TRAILING_SPACE) {
      state = OUT_TRAILING_SPACE;
      if (i < (limit - 1)) {
        line[i] = c;
      } 
      ++i;
    } 
  }
  if (c == '\n') {
    if (i < (limit - 1)) {
      line[i] = c;
    }
    ++i;
  }
  if (!i) {
    return 0;
  }
  (state == IN_TRAILING_SPACE) ? (line[0] = '\0') : (line[i] = '\0');
  return i;
}

