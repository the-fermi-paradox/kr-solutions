#include <stdio.h>
#define swap(t, x, y) { int tmp = t[x]; t[x] = t[y]; t[y] = tmp; }

int main() {
  int arr[] = {0, 1, 2};
  swap(arr, 0, 2);
  for (int i = 0; i < 3; ++i) {
    printf("%d\n", arr[i]);
  }
}
