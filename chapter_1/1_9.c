// Exercise 1-9
// Replace Blanks
// Write a program to copy its input to its output, replacing
// each string of one or more blanks by a single blank.
#include <stdio.h>

int main() {
  int i;
  int c;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      i++;
      if (i > 1) {
        continue;
      } 
    } else {
      i = 0;
    }
    putchar(c);
  }
}
