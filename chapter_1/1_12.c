// Exercise 1-12
// Print Word
// Write a program that prints its input one word per line.
#include <stdio.h>
#define OUT 0
#define IN 1

int main() {
  int c;
  int morenone = 0;
  while ((c = getchar()) != EOF) {
    if ((c == '\n' || c == ' ' || c == '\t')) {
      if (!morenone) {
        putchar('\n');
        morenone = 1;
      }
    } else {
      morenone = 0;
      putchar(c);
    }
  }
}
