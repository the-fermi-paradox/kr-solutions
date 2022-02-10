/* Exercise 3-4: itoa
 * In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to (-2^n -1)
 * Explain why not. Modify it to print that value correctly, regardless of the 
 * machine on which it runs. */

/* Explanation:
 * Two's complement number system takes the space in 2^n, where n is # of bits,
 * and divides it in half: 2^(n-1). First half is nonnegative, second is negative.
 * One number in the nonnegatives is used for zero, so -1.
 * So for any x in our system: -2^(n-1) <= x <= 2^(n-1)-1.
 * Notice: if x = -2^(n-1) * -1 = 2^(n-1) which means x > 2^(n-1)-1
 * This is an overflow and outside the bounds of the number system. 
 * To solve this, in itoa, we make positives negative instead of negatives positive
 * because there is more space in the negatives.*/

#include <stdio.h>
#define MAX_SIZE 1000
void itoa(int n, char s[]);
void reverse(char s[]);
int main() {
  char s[MAX_SIZE];
  itoa(987654321, s);
  printf("%s", s);
}
void itoa(int n, char s[]) {
  int i, sign;
  if ((sign = n) > 0) { /* record sign */
    n = -n;             /* make n negative */
  }
  i = 0;
  do {
    s[i++] = -(n % 10) + '0';
  } while ((n /= 10) < 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
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
