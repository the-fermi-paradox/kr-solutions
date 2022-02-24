#include <stdio.h>
#include <ctype.h>
static int atoi(char* s);
static int cgetline(char* line, int limit);
static char* itoa(int i, char* str, int base);
static int pop(void);
static int* push(int i);
static char* reverse(char* str);
static int strindex(char* s, char* t);

#define MAXINT 100
int main()
{
  char line[MAXINT];
  char tocheck[] = "hello";
  char intg[MAXINT];
  while (cgetline(line, MAXINT) > 0) {
    int i = atoi(line);
    printf("%d\n", strindex(line, tocheck));
    printf("%s\n", reverse(line));
    printf("dec:\t%s\n", itoa(i, intg, 10));
    printf("hex:\t%s\n", itoa(i, intg, 16));
    printf("oct:\t%s\n", itoa(i, intg, 8));
    printf("bin:\t%s\n", itoa(i, intg, 2));
  }
}
static int cgetline(char* line, int limit)
{
  if (!line) return -1;
  int c;
  char* lpnt = line;
  while ((c = getchar()) != EOF) {
    if (lpnt - line < (limit - 1)) {
      *lpnt++ = c;
    }
    if (c == '\n') {
      break;
    }
  }
  if (lpnt - line == 0) {
    return 0;
  }
  *lpnt++ = '\0';
  return lpnt - line;
}

static int atoi(char* s)
{
  if (!s) return -1;
  /* skip whitespace */
  for (;isspace(*s); ++s);
  /* grab sign */
  int sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+') ++s;
  int n;
  for(n = 0; isdigit(*s); ++s) {
    n = n * 10 + (*s - '0');
  }
  return n * sign;
}

#define EMPTY -1
#define POSITIVE 1
#define NEGATIVE -1
static char* itoa(int i, char* str, int base)
{
  if (!str) return str;

  int sign = POSITIVE;
  if (i < 0) {
    i = -i;
    sign = NEGATIVE;
  }
  do {
    push(i);
    i /= base;
  } while (i > 0);

  int c;
  char* lpnt = str;
  if (sign == NEGATIVE) {
    *lpnt++ = '-';
  }
  int mod;
  while ((c = pop()) != EMPTY) {
    mod = c % base;
    *lpnt++ = mod + ((mod >= 10) ? 'A' - 10 : '0'); 
  }
  *lpnt++ = '\0';
  return str;
}

static char* reverse(char* str)
{
  if (!str) return str;

  char* lpnt, *rpnt;
  char tmp;
  for (lpnt = rpnt = str; *rpnt; ++rpnt);
  for (--rpnt; lpnt < rpnt; ++lpnt, --rpnt) {
    tmp = *lpnt;
    *lpnt = *rpnt;
    *rpnt = tmp;
  }
  return str;
}

static int strindex(char* s, char* t)
{
  if (!s || !t) return -1;

  char* opnt, *inpnt;
  int i, index;

  for (i = 0, opnt = s, inpnt = t; *opnt; ++opnt, ++i) {
    /* Once we reach the end of the check string, we're done */
    if (!*inpnt) {
      return index;
    } 

    /* Reset */
    if (*opnt != *inpnt) {
      inpnt = t;
    } else if (inpnt == t) {
    /* Save the index of the first matching character */
      index = i;
      ++inpnt;
    } else {
      ++inpnt;
    }
  }
  return -1;
}

/* stack implementation*/
#define MAX 1000
static int vals[MAX];
static int* valp = vals;
static int pop(void)
{
  if (!(valp - vals))
    return EMPTY;
  return *--valp;
}
static int* push(int i)
{
  if (valp - vals >= MAX)
    return NULL;
  *valp++ = i;
  return valp;
}
