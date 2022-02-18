static void swap(char a[], int i, int j);
static int reverse(char a[], int i);
#include <stdio.h>
int main(void) {
  char a[] = "abcdefghijklmnop   qrstuvwxyz";
  reverse(a, 0);
  printf("%s\n", a); 
}

static int reverse(char a[], int i) {
  if (a[i] == '\0') {
    return 0;
  }
  int j = reverse(a, i + 1);
  if (j < i)
    swap(a, i, j);
  return j + 1;
}

static void swap(char a[], int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}
