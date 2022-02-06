#include <stdio.h>
void squeeze(char s1[], char s2[]);
int main() {
  char original[] = "this is the original";
  char badchars[] = "this";
  printf("original: %s\nbadchars: %s\n", original, badchars);
  squeeze(original, badchars);
  printf("stripped: %s\n", original);
}

void squeeze(char s1[], char s2[]) {
  int i = 0;
  int k = 0;
  int j;
  int match;
  while (s1[i] != '\0') {
    match = 0;
    j = 0;
    while (s2[j] != '\0') {
      if (s1[i] == s2[j]) {
        match = 1;
        break;
      }
      ++j; 
    }
    if (!match) {
      s1[k++] = s1[i];
    }
    ++i;
  }
  s1[k] = '\0';
}
