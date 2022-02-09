#include <stdio.h>
int binarysearch(int x, int v[], int n);
int oldbinarysearch(int x, int v[], int n);

int main() {
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  printf("%d", binarysearch(8, arr, 11));
  printf("%d", oldbinarysearch(8, arr, 11));
}

int oldbinarysearch(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int binarysearch(int x, int v[], int n) {
  int low = 0;
  int high = n - 1;
  int mid;
  while (low <= high && v[(mid = (high + low) / 2)] != x) {
    (x < v[mid]) 
    ? (high = mid - 1) 
    : (low = mid + 1);
  }
  return (v[mid] == x) ? mid : -1;
}
