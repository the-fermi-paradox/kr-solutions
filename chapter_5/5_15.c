#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINES 5000
#define NUMERIC 1
#define REVERSE 2
#define FOLD    4
char *lineptr[MAXLINES];

int strcmp1(const char *s1, const char *s2);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsortc(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);

static int options;

int main(int argc, char* argv[])
{
  int nlines;

  for (++argv; argc-- > 1; ++argv) {
    if (**argv != '-') {
      ++argv;
      continue;
    }

    while (**argv) {
      if (**argv == 'n') {
        options |= NUMERIC;
      }
      if (**argv == 'r') {
        options |= REVERSE;
      }
      if (**argv == 'f') {
        options |= FOLD;
      }
      (*argv)++;
    }
  }

  int (*func)(void*, void*) = (int (*)(void*, void*))((options & NUMERIC) ? numcmp : strcmp1);

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsortc((void **) lineptr, 0, nlines-1, func);
    writelines(lineptr, nlines);
    return 0;
  }
  printf("input too big to sort\n");
  return 1;
}

void qsortc(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
  int i, last, reverse;
  void swap(void *v[], int, int);

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right)/2);
  last = left;
  reverse = options & REVERSE;
  for (i = left+1; i <= right; i++) {
    if ((reverse && (*comp)(v[i], v[left]) > 0)
    || (!reverse && (*comp)(v[i], v[left]) < 0)) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsortc(v, left, last-1, comp);
  qsortc(v, last+1, right, comp);
}

#include <stdlib.h>
int numcmp(const char *s1, const char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2) {
    return -1;
  }
  else if (v1 > v2) {
    return 1;
  }
  else {
    return 0;
  }
}

int strcmp1(const char *s1, const char *s2)
{
  int fold = options & FOLD;
  while (s1 && s2 && (fold) ? toupper(*s1) == toupper(*s2) : *s1 == *s2) {
    ++s1, ++s2;
  }
  return (fold) ? toupper(*s1) - toupper(*s2) : *s1 - *s2;
}

void swap(void *v[], int i, int j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int readline(char* line, int n)
{
  int c;
  char* i = line;
  while (line - i < n - 1 && (c = getchar()) != EOF) {
    *line++ = c;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  *line = '\0';
  return line - i;
}

int readlines(char *lineptr[], int maxlines)
{
  #define MAXLEN 1000
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = readline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  printf("final output:\n");
  printf("[");
  while (nlines-- > 0) {
    printf("%s", *lineptr++);
    if (nlines != 0) {
      printf(",");
    }
  }
  printf("]\n");
}

