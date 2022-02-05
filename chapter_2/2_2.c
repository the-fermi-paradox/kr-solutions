/* Exercise 2_2
 * Write a loop equivalent to the for loop 
 * above without using && or ||
 */
#include <stdio.h>

int main() {
  int lim = 500;
  char s[lim];
  int c, i;
  i = 0;
  while (i < lim - 1) {
    if ((c = getchar()) == '\n') {
      break;
    }
    if (c == EOF) {
      break;
    }
    s[i] = c;
    ++i;
  }
  printf("%s", s);
}
