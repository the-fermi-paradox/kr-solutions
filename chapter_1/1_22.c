// Exercise 1.22
// FOLDING
// Write a program to "fold" long input lines into two or more
// shorter lines after the last non-blank character before the nth 
// column of input. Make sure your program does something intelligent
// with very long lines, and if there are no blanks or tabs before
// the specified column.
#include <stdio.h>
#define MAX_SIZE 1000
#define MAX_LENGTH 10

void process(char from[], char to[]);
int readline(char line[], int lim);
int main() {
  char line[MAX_SIZE];
  char to[MAX_SIZE];
  int size;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    process(line, to);
    printf("%s", to);
  }
}

void process(char from[], char to[]) {
  int k = 0;
  int i = 0;
  int newline = 0;
  int inword = 0;
  while (from[i] != '\0') {
    if (from[i] == ' ' || from[i] == '\t' || from[i] == '\n') {
      inword = 0;
      to[k] = from[i]; 
      ++i;
      ++k;
      if ((k + 1) % MAX_LENGTH == 0) {
        newline = 1;
      }
    } else if (newline) {
      newline = 0;
      to[k] = '\n';
      ++k;
    } else {
      if ((k + 1) % MAX_LENGTH == 0) {
        newline = 1;
      }
      if (newline && inword) {
        to[k] = '-';
        ++k;
      } else { 
        inword = 1;
        to[k] = from[i];
        ++i;
        ++k;
      }
    }
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
