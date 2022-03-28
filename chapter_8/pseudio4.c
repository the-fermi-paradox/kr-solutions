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
  int n;
  FILE *fp;
  if (argc == 1) {
    error("usage: massinput f1 f2 f3");
  }
  while (--argc > 0) {
    if (fopen(*++argv, "w") == NULL)
      error("error: failed to open file");
  }
  while ((n = getc(stdin)) != EOF) {
    for (fp = _iob; fp < _iob + OPEN_MAX; ++fp) {
      if (fp->flag.write)
        putc(n, fp);
    }
  }
  fcloseall(fp);
  return 0;
}
