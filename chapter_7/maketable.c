#include <stdio.h>
int main(void)
{
  for (int i = 0; i < 128; ++i) {
    printf("%d", i >= 'A' && i <= 'Z');
    if (i != 127) {
      printf(",");
    }
  }
}
