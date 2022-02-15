#include <stdio.h>
#include <string.h>
void ungetch(int c);
int ungets(char s[]) {
  int i;
  for (i = strlen(s) - 1; i >= 0; --i) {
    ungetch(s[i]);
  }
  return i;
}

/* getch and ungetch */
#define MAXBUF 100
int bufp;
int buf[MAXBUF];

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= MAXBUF) {
    printf("error: buf size exceeded\n");
    return;
  }
  buf[bufp++] = c;
}
