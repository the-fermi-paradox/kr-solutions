/* Exercise 5-13: Tail */

#include <stdio.h>
#include <stdlib.h>
#define DEFAULT 10
int readline(char* line, int lim);

int main(int argc, char* argv[]) {
  if (argc > 2) {
    printf("error: too many arguments\n");
    return 1;
  }
  ++argv;
  int tail = (argc > 1 && **argv == '-') ? atoi(*argv + 1) : DEFAULT;
  if (!tail)
    tail = DEFAULT;

  #define CONTENT 10000
  char line[CONTENT];
  #define MAXLINES 5000
  char* pntrs[MAXLINES];

  char** pnt = pntrs;
  char* lpnt;
  int n;
  for (lpnt = line; (n = readline(lpnt, CONTENT)) > 0; lpnt += n) {
    *pnt++ = lpnt;
  }
  char** rpnt = (pnt - tail < pntrs) ? pntrs : pnt - tail;
  while (rpnt < pnt) {
    printf("%s", *rpnt++); 
  }
  return 0;
}

int readline(char* line, int lim) {
  int c;
  char* orig = line;
  while (line - orig < lim - 1 && (c = getchar()) != EOF) {
    *line++ = c;
    if (c == '\n') {
      break;
    }
  }
  if (line == orig) {
    return -1;
  }
  *line++ = '\0';
  return line - orig;
}
