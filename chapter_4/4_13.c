static void swap(char a[], int i, int j);
static void reverse(char a[]);
static int _reverse(char a[], int i);
#include <stdio.h>
int main(void) {
  char a[] = "ab";
  reverse(a);
  printf("%s\n", a); 
}

static int _reverse(char a[], int i) {
  if (a[i] == '\0') {
    return 0;
  }
  int j = _reverse(a, i + 1);
  if (j < i)
    swap(a, i, j);
  return j + 1;
}

/* Add a wrapper so we don't need to supply 0 as a consumer of the function*/
static void reverse(char a[]) {
  _reverse(a, 0);
}

static void swap(char a[], int i, int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}
