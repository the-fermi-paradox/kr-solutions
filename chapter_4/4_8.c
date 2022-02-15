#include <stdio.h>
#include <string.h>
int ungetch(int c);

/* getch and ungetch */
/* Only one character of pushback */
int buf = -1;

int getch(void) {
  int tmp;
  if (buf >= 0) {
    tmp = buf;
    /* Clear the buffer */
    buf = -1;
    return tmp;
  }
  return getchar();
}

int ungetch(int c) {
  /* Can only ungetch one character at a time */
  if (buf >= 0) {
    return 1;
  }
  buf = c;
  return 0;
}
