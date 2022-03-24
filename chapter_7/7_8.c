#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000
#define MAXFILES 50

/* Colors */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct FILEPATH {
  FILE *fp;
  char *path;
};

struct FILEPATH* createpath(char *path)
{
  struct FILEPATH* fpp;
  fpp = malloc(sizeof(*fpp));
  fpp->fp = fopen(path, "r");
  if (fpp->fp == NULL) {
    printf("find: error opening '%s'\n", path);
    exit(1);
  }
  fpp->path = strdup(path);
  return fpp;
}

void freepath(struct FILEPATH* fpp)
{
  fclose(fpp->fp);
  free(fpp->path);
  free(fpp);
}

#define PAGEMAX 52

int main(int argc, char *argv[])
{
  struct FILEPATH *files[MAXFILES] = {NULL};
  struct FILEPATH **filesp = files;
  char line[MAXLINE];

  while (--argc > 0) {
    ++argv;
    *filesp++ = createpath(*argv);
  }
  if (filesp == files) {
    printf("Usage: pager f1 f2 .. fx \n");
  }
  else {
    for (filesp = files; *filesp != NULL; freepath(*filesp), filesp++) {
      long lineno = 0;
      long pageno = 0;
      /* Always print header at start of file */
      printf("\n\n" ANSI_COLOR_CYAN "----------%s----------\n\n" ANSI_COLOR_RESET, (*filesp)->path);
      while (fgets(line, MAXLINE, (*filesp)->fp)) {
        ++lineno;
        /* Print header to start a new page */
        if (lineno % PAGEMAX == 0) {
          printf("\n\n" ANSI_COLOR_CYAN "----------%s----------\n\n" ANSI_COLOR_RESET, (*filesp)->path);
        }
        printf("%s ", line);
        /* Print footer if we're about to go to a new page */
        if (lineno % PAGEMAX == PAGEMAX - 1) {
          printf("\n\n" ANSI_COLOR_CYAN "----------%ld----------\n\n" ANSI_COLOR_RESET, ++pageno);
        }
      }
      /* Always print footer at the end of file */
      printf("\n\n" ANSI_COLOR_CYAN "----------%ld----------\n\n" ANSI_COLOR_RESET, ++pageno);
    }
  }
  return 0;
}
