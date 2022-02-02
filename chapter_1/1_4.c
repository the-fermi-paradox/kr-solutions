#include <stdio.h>
#define UPPER 300
#define LOWER -100
#define STEP 20

int main() {
  float cels, fahr;
  for (cels = UPPER; cels >= LOWER; cels -= STEP) {
    fahr = (9.0/5.0) * cels + 32;
    printf("%3.0f\t%6.1f\n", cels, fahr);
  }
}
