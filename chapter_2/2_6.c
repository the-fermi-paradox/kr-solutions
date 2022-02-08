#include <stdio.h>
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);


int main() {
  printf("%X\n", setbits(
        0xf01, // 111100000001
        5,
        3,
        0x3f5) // 001111110101 
               // 111100101001 
               // 0xf29
      );
}

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
  /* We don't want to shift negative */
  if (n > p + 1) return x;
  unsigned shift = p + 1 - n;
  
  /* First clear the bits in x
   * then get only the least sig bits in y (up to n)
   * shift them so they line up
   * then set the newly cleared bits in x equal to the bits in y
   */
  return (x & ~(~(~0 << n) << shift)) | ((~(~0 << n) & y) << shift);
}
