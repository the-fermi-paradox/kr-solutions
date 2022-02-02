// Exercise 1-8
// Count Blanks
// Write a program to count blanks, tabs and newlines.
#include <stdio.h>

int main() {
  int i;
  int c;
  while ((c = getchar()) != EOF)
    if (c == '\n' || c == ' ' || c == '\t') i++;
  printf("%d\n", i);
}
