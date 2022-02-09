#include <stdio.h>

unsigned bitcount(unsigned x);
int main() {
  printf("%u", bitcount(0xfff)); 
}

unsigned bitcount(unsigned x) {
  int b = 0;
  while (x != 0) {
    x &= x - 1;
    ++b;
  }
  return b;
}
