/* Exercise 3-5: itob
 * Write the function itob(n, s, b) that converts the integer n into a base b
 * character representation in the string s. In particular, itob(n,s,16) formats
 * n as a hexadecimal integer in s. 
 */
#include <stdio.h>
#define MAX_BASE 72
int itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
  char s[1000];
  if (itob(71, s, 72)) return 1;
  printf("%s", s);
  return 0;
}

int itob(int n, char s[], int b) {
  int i, sign, modulo;
  if (b > MAX_BASE) {
    return 1;
  }
  if ((sign = n) > 0) { /* record sign */
    n = -n;             /* make n negative */
  }
  i = 0;
  do {
    modulo = -(n % b);
    /* Adjust modulo if greater than 10 so 10 and up are single characters
     * There's a limit on how much sense this makes. For larger bases (42+), results
     * are case sensitive. Very large bases (73+) can't be represented at all.*/
    if (modulo >= 10) {
      s[i++] = (modulo - 10) + 'A';
    } else {
      s[i++] = modulo + '0';
    }
  } while ((n /= b) < 0);
  if (sign < 0) {
    s[i++] = '-';
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
