#include <stdio.h>
int readline(char line[], int lim);
double powa(double term, int times);
int atoi(char a[]);
const int MAX_SIZE=1000;

int main() {
  char line[MAX_SIZE];
  while (readline(line, MAX_SIZE) > 0) {
    int val = atoi(line);
    printf("%d\n", val);
  }
}

int atoi(char a[]) {
  int i;
  int ret = 0;
  int size = 0;
  int sign = 1;
  for (i = 0; a[i] != '\n'; ++i) {
    if (i == 0 && a[i] == '-') {
      sign = -1;
    } else if (a[i] < '0' || a[i] > '9') {
      return ret;
    }
    ++size;
  }
  for (i = 0; a[i] != '\n'; ++i) {
    int magn = a[i] - '0';
    int place = powa(10.0, size - 1);
    ret += magn * place;
    --size;
  }
  return ret * sign;
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

int readline(char line[], int lim) {
  int c;
  int i = 0;
  while ((c = getchar()) != EOF) {
    if (i < lim - 1) {
      line[i] = c;
    }
    ++i;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  line[i] = '\0';
  return i;
}
