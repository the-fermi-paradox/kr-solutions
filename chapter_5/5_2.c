/* 
 * Exercise 5-1
 * As written, getfloat treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 */
#include <stdio.h>
#include <ctype.h>
static int getch(void);
static void ungetch(int c);
static int getfloat(double *pn);

int main(void) {
  #define SIZE 100
  double arr[SIZE];
  int n;
  int c;
  for (n = 0; n < SIZE && (c = getfloat(&arr[n])) != EOF && c != 0; ++n);
  int i;
  for (i = 0; i < n; ++i)
    printf("i: %d\tv: %f\n", i, arr[i]);
}

static int getfloat(double *pn) {
  int c, sign;

  while (isspace(c = getch()));
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c)) {
      ungetch(c);
      return 0;
    }
  }
  /* Integer part */
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  /* Fraction part */
  if (c == '.') {
    int plc;
    for (plc = 1; isdigit(c = getch()); plc *= 10)
      *pn = *pn + ((float)(c - '0') / (plc * 10));
    /* The next character wasn't a digit */
    if (plc == 1) {
      ungetch(c);
      return 0;
    }
  }
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

#define MAXBUF 100
int buf[MAXBUF];
int bufp;

static int getch(void) {
  return bufp ? buf[--bufp] : getchar();
}

static void ungetch(int c) {
  if (bufp < MAXBUF)
    buf[bufp++] = c;
}
