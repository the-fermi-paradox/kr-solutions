#include <stdio.h>
#define MAX_SIZE 1000
#define IN_TRAILING_SPACE 0
#define OUT_TRAILING_SPACE 1

int readline(char line[], int limit);
int reverse(char line[], int limit);

int main() {
  char line[MAX_SIZE];  
  int size;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    reverse(line, size);
    printf("%s", line);
  }
}

int readline(char line[], int limit) {
  int c, i;
  i = 0;
  while ((c = getchar()) != EOF && c != '\n') {
    if (i < (limit - 1)) {
      line[i] = c;
    } 
    ++i;
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

  line[i] = '\0';
  return i;
}

int reverse(char line[], int limit) {
  char storage;
  int i, j;

  for (i = 0, j = limit - 2; i < j; ++i, --j) {
    storage = line[j];
    line[j] = line[i];
    line[i] = storage;
  }
  line[limit + 1] = '\0';
  return 0;
}
