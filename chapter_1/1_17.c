// Exercise 1-17
// Print Long Lines
// Write a program to print all input lines that are longer
// than 80 characters
#include <stdio.h>
#define MAX_SIZE 1000
int readline(char line[], int limit);

int main() {
  char line[MAX_SIZE];  
  int size;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    if (size >= 80) {
      printf("%s", line);
    }
  }
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
