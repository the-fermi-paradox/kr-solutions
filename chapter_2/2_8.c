#include <stdio.h>
#include <limits.h>
void printbinary(unsigned x);
unsigned rightrot(unsigned x, unsigned n);
#define SAMPLE_VAR 0x000f
int main() {
  printbinary(SAMPLE_VAR);
  printbinary(rightrot(SAMPLE_VAR, 3));
  return 1;
}
unsigned rightrot(unsigned x, unsigned n) {
  unsigned mask = (x & ~(~0 << n)) << (sizeof(unsigned) * CHAR_BIT - n);
  return (x >> n) | mask;
}

void printbinary(unsigned x) {
  int bits = sizeof(unsigned) * CHAR_BIT - 1;
  int i = 0;
  while (i <= bits) {
    putchar(((x & (1 << (bits - i))) >> (bits - i)) + '0');
    ++i;
  }
  putchar('\n');
}
