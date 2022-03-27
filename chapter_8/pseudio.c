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
  int buf[BUFSIZ];
  int n;
  FILE *fp;
  while (--argc > 0) {
    if ((fp = fopen(*++argv, "r")) == NULL)
      error("error: failed to open file");
    while ((n = read(fp->fd, buf, BUFSIZ)) > 0)
      if (write(STDOUT, buf, n) != n)
        error("error: failed to write file contents");
  }
  return 0;
}
