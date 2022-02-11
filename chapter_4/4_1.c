#include <stdio.h>
int readline(char line[], int lim);
int strrindex(char s[], char t[]);
int main() {
  char s[1000];
  char t[] = "Hello";
  while (readline(s, 1000) > 0) {
    int i = strrindex(s, t);
    printf("%d\n", i);
  }
}
int strrindex(char s[], char t[]) {
  int i, k, j;
  int saved = -1;
  for (i = 0; s[i] != '\0'; ++i) {
    for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; ++k, ++j) {
    };
    if (t[k] == '\0' && k > 0) {
      saved = i;
    }
  }
  return saved;
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
