#include <stdio.h>
void printd(int i);

int main(void) {
  printd(500);
}

void printd(int i) {
  if (i < 0) {
    putchar('-');
    i = -i;
  }
  if (i < 10) { 
    putchar(i + '0');
    return;
  }
  printd(i / 10);
  putchar((i % 10) + '0');
}
