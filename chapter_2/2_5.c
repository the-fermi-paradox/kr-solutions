#include <stdio.h>
int any(char s1[], char s2[]);
int main() {
  char original[] = "this is the original";
  char badchars[] = "nt";
  printf("original: %s\nbadchars: %s\n", original, badchars);
  printf("location: %d\n", any(original, badchars));
}

int any(char s1[], char s2[]) {
  int i = 0;
  int j;
  while (s1[i] != '\0') {
    j = 0;
    while (s2[j] != '\0') {
      if (s1[i] == s2[j]) {
        return i;
      }
      ++j; 
    }
    ++i;
  }
  return -1;
}
