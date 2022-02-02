#include <stdio.h>

float fahrToCels(float fahr);

int main() {
  float cels;
  int lower = 0;
  int upper = 300;
  int step = 20;
  printf("%3s\t%6s\n", "F", "C");
  for (float fahr = lower; fahr <= upper; fahr += step) {
    cels = fahrToCels(fahr);
    printf("%3.0f\t%6.1f\n", fahr, cels);
  }
}

float fahrToCels(float fahr) {
  return (fahr - 32) * (5.0 / 9.0);
}
