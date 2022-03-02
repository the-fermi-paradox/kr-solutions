#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], char text[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

#define MAXCONTENT 10000
/* sort input lines */
int main(void)
{
  int nlines; /* number of input lines read */
  char text[MAXCONTENT];
  if ((nlines = readlines(lineptr, text, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000
int ggetline(char* line, int);
int ggetline(char* line, int n)
{
  int c, i;
  i = 0;
  while (i < n - 1 && (c = getchar()) != EOF) {
    *line++ = c;
    ++i;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  *line = '\0';
  return i;
}

/* readlines: read input lines */

int readlines(char *lineptr[], char text[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  p = text;
  while ((len = ggetline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p - text + len) >= MAXCONTENT) {
      return -1;
    }
    line[len - 1] = '\0'; /* delete newline */
    strcpy(p, line);
    lineptr[nlines++] = p;
    p += len;
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

void swap(char *v[], int i, int j);
void qsort(char *lineptr[], int left, int right)
{
  if (left >= right) {
    return;
  }
  swap(lineptr, (right + left) / 2, right);
  int i, j;
  for (i = left - 1, j = left; j < right; ++j) {
    if (strcmp(lineptr[j], lineptr[right]) <= 0) {
      ++i;
      swap(lineptr, i, j); 
    }
  }

  swap(lineptr, i + 1, right);
  qsort(lineptr, left, i);
  qsort(lineptr, i + 2, right);
}

void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
