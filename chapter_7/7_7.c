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

int main(int argc, char *argv[])
{
  struct FILEPATH *files[MAXFILES] = {NULL};
  struct FILEPATH **filesp = files;
  int showpath = 1;
  char line[MAXLINE];
  char pattern[MAXLINE];
  int pattern_found = 0;
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  while (--argc > 0) {
    if (**++argv == '-') {
      while ((c = *++*argv)) {
        switch(c) {
        case 'x':
          except = 1;
          break;
        case 'n':
          number = 1;
          break;
        case 'p':
          showpath = 1;
          break;
        case 'z':
          showpath = 0;
          break;
        default:
          printf("find: illegal option %c\n", c);
          argc = 0;
          found = -1;
          break;
        }
      }
    } else if (!pattern_found) {
      pattern_found = 1;
      strcpy(pattern, *argv);
    } else {
      *filesp++ = createpath(*argv);
    }
  }
  if (argc != 0 || !pattern_found) {
    printf("Usage: find -x -n pattern\n");
  } else if (filesp == files) {
    while (fgets(line, MAXLINE, stdin)) {
      lineno++;
      if((strstr(line, pattern) != NULL) != except) {
        if (number) {
          printf("%ld:", lineno);
        }
        printf("%s", line);
        found++;
      }
    }
  } else {
    for (filesp = files; *filesp != NULL; freepath(*filesp), filesp++) {
      lineno = 0;
      while (fgets(line, MAXLINE, (*filesp)->fp)) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
          if (showpath) {
            printf(ANSI_COLOR_CYAN "%s " ANSI_COLOR_RESET, (*filesp)->path);
          }
          if (number) {
            printf(ANSI_COLOR_RED "%ld:" ANSI_COLOR_RESET, lineno);
          }
          printf("%s", line);
          found++;
        }
      }
    }
  }
  return 0;
}
