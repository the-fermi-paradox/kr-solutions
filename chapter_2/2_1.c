#include <stdio.h>
#define F_EXPONENT_MAX 127
#define D_EXPONENT_MAX 1023
#define BASE 2.0
#define BITS_IN_BYTE 8

double get_mepsilon(int p);
double powa(double term, int times);
void get_frange(char typ[], double base, int p);
void get_nrange(char typ[], int size);

int main() {
  get_frange("float", BASE, F_EXPONENT_MAX);
  get_frange("double", BASE, D_EXPONENT_MAX);
  get_nrange("char", sizeof(char));
  get_nrange("int", sizeof(int));
  get_nrange("short", sizeof(short));
  get_nrange("long", sizeof(long));
}

void get_nrange(char typ[], int size) {
  /* half are negatives; -2^(size - 1) */
  long int min = powa(2, size * BITS_IN_BYTE - 1) *-1;
  /* half are positives; 2^(size - 1) - 1 */
  long int max = powa(2, size * BITS_IN_BYTE - 1) -1;
  printf("%s\n-------\nmin: %.3ld\nmax: %.3ld\n\n", typ, min, max);
}

void get_frange(char typ[], double base, int p) {
  /* the mantissa APPROACHES the base when all bits are 1 
   * (the series 2^-n converges to 2 as n approaches infinity). 
   * this is thus an approximation! */
  double mantissa = 1.999999;
  double min = -1 * mantissa * powa(base, p);
  double max = mantissa * powa(base, p);
  printf("%s\n-------\nmin: %.3g\nmax: %.3g\n\n", typ, min, max);
  
}

/* machine epsilon for the given precision */
double get_mepsilon(int p) {
  return powa(BASE, -(p - 1));
}

double powa(double term, int times) {
  if (times == 0) {
    return 1;
  } 
  if (times == 1) {
    return term;
  } 
  if (times < 0) {
    return 1 / powa(term, times * -1);
  }
  return (term * powa(term, times - 1));
}
