#include <ctype.h>
#include <stdio.h>
#define MAX_SIZE 1000
int readline(char line[], int lim);
int expand(char s1[], char s2[]);

int main() {
  char s1[MAX_SIZE];
  char s2[MAX_SIZE];
  while (readline(s1, MAX_SIZE) > 0) {
    expand(s1, s2);
    printf("%s", s2);
  }
  return 1;
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

int expand(char s1[], char s2[]) {
  int i, k;
  i = k = 0;
  while (s1[i] != '\0') {
    /* If we have a '-', the previous and next character 
     * must be of the same type for it to be expandable */
    if (s1[i + 1] == '-' 
        && ((islower(s1[i]) && islower(s1[i + 2]))
         || (isupper(s1[i]) && isupper(s1[i + 2]))
         || (isdigit(s1[i]) && isdigit(s1[i + 2])))) {
      /* Insert the leading character */
      s2[k] = s1[i];
      ++k;
      /* We expand up */
      if (s1[i] <= s1[i + 2]) {
        while ((s2[k] = s2[k - 1] + 1) < s1[i + 2]) {
          ++k;
        }
      /* Or we expand down */
      } else {
        while ((s2[k] = s2[k - 1] - 1) > s1[i + 2]) {
          ++k;
        }
      }
      /* This preserves the last character for expansions of form 'a-b-e' */
      i += 2;
    } else {
      s2[k] = s1[i];
      ++k;
      ++i;
    }
  }
  s2[k] = '\0';
  return 1;
}
