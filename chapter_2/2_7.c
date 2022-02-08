#include <stdio.h>
#include <limits.h>
unsigned invert(unsigned x, unsigned p, unsigned n);
void printbinary(unsigned x);

#define SAMPLE_VAR 0xff5

int main() {
  printbinary(SAMPLE_VAR);
  printbinary(invert(SAMPLE_VAR, 4, 3));
}

unsigned invert(unsigned x, unsigned p, unsigned n) {
  return x ^ (~(~0 << n) << (p + 1 - n));
}

void printbinary(unsigned x) {
  int bits = sizeof(unsigned) * CHAR_BIT;
  int i = 0;
  while (i <= bits) {
    putchar(((x & (1 << (bits - i))) >> (bits - i)) + '0');
    ++i;
  }
  putchar('\n');
}
