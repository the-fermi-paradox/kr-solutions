/* Exercise 3-6: itoa field width
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must be
 * padded with blanks on the left if necessary to make it wide enough.
 */
#include <stdio.h>
#define MAX_BASE 72
int itoa(int n, char s[], int fw);
void reverse(char s[]);

int main() {
  char s[1000];
  itoa(50, s, 15);
  printf("%s", s);
  return 0;
}

int itoa(int n, char s[], int fw) {
  int i, sign;
  if ((sign = n) > 0) {
    n = -n; 
  }
  i = 0;
  do {
    s[i++] = -(n % 10) + '0';
  } while ((n /= 10) < 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  while (i < fw) {
    s[i++] = ' ';
  }
  s[i] = '\0';
  reverse(s);
  return 0;
}

/* Reverse in place */
void reverse(char s[]) {
  int i, k, temp;
  for (k = 0; s[k] != '\0'; ++k); /* Get length of string */
  for (i = 0, --k; i < k; ++i, --k) {
    temp = s[i]; 
    s[i] = s[k];
    s[k] = temp;
  }
}

