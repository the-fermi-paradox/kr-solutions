static char s[500];
static int sp;
static void itoa(int n);
static void rout(int n);
#include <stdio.h>
int main() {
  itoa(-158);
  printf("%s\n", s);
  itoa(-4);
  printf("%s\n", s);
  itoa(-40925);
  printf("%s\n", s);
  itoa(5);
  printf("%s\n", s);
}

/* We split the program into two functions;
 * one itoa to handle cleanup that only runs on first call
 * and rout to serve as our main recursive routine */
static void itoa(int n) {
  sp = 0;
  if (n < 0) {
    s[sp++] = '-';
    n = -n;
  }
  rout(n / 10);
  s[sp++] = (n % 10) + '0';
  s[sp++] = '\0';
}

static void rout(int n) {
  if (n == 0)
    return;
  rout(n / 10);
  s[sp++] = (n % 10) + '0';
}
