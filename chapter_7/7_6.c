/* Exercise 7-6: Diff */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LMAX 1000
int main(int argc, char **argv)
{
  if (argc < 3) {
    fprintf(stderr, "diff: missing operand after '%s'\n", argv[argc - 1]);
    exit(1);
  } else if (argc > 3) {
    fprintf(stderr, "diff: extra operand '%s'\n", argv[4]);
    exit(2);
  }
  /* argc should be 3 */
  FILE *fp = fopen(*++argv, "r");
  FILE *fp2 = fopen(*++argv, "r");
  if (!fp) {
    fprintf(stderr, "diff: can't open %s\n", *(argv - 1));
    exit(3);
  }
  if (!fp2) {
    fprintf(stderr, "diff: can't open %s\n", *argv);
    exit(3);
  }
  char line[LMAX];
  char line2[LMAX];
  int i = 0;
  char* tmp;
  do {
    /* Necessary to avoid short-circuiting */
    tmp = fgets(line2, LMAX, fp2);
    if (fgets(line, LMAX, fp) == NULL || tmp == NULL)
      break;
    ++i;
  } while(strcmp(line, line2) == 0);
  /* The entire file was read in both cases; the files are the same */
  if (feof(fp) && feof(fp2))
    exit(0);

  if (ferror(fp) || ferror(fp2)) {
    fprintf(stderr, "diff: error reading from file\n");
    exit(4);
  }
  printf("|%d:%s|%d:%s\n", i, line, i, line2);
  exit(0);
}
