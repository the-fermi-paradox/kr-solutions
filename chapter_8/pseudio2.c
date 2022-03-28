#include "pseud.h"
#define errmesg "an error occurred\n"
#define STDIN  0
#define STDOUT 1
#define STDERR 2

void error(const char *s)
{
  write(STDERR, s, sizeof(s));
  exit(1);
}

int main(int argc, char **argv)
{
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
  }
  return 0;
}
