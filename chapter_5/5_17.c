#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINES 5000
#define NUMERIC 1
#define REVERSE 2
#define FOLD    4
#define DIRECT  8
#define FIELD   16
#define NEXTED  32
char *lineptr[MAXLINES];

int numcmp(const char *, const char *);
void qsortc(void *v[], int left, int right, int (*comp)(void *, void *));
void reverse(const char *s1, const char *s2);
int isspaceoralnum(char s);
int cmp(const char *s1, const char *s2);
const char* get_field_ptr(const char *s, int fieldmax);
int fieldcmp(const char *s1, const char *s2);
int numcmp(const char *s1, const char *s2);
int strcmp1(const char *s1, const char *s2);
void swap(void *v[], int i, int j);
int readline(char* line, int n);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

#define NONUM -1
#define STRAYCHAR -2
#define BADMEM -3
static int stray;
int countdigits(char *field)
{
  if (!field) return 0;
  char* tmp = field;
  while (isdigit(*tmp)) {
    ++tmp;
  }
  return tmp - field + 1;
}

static int options;
#define MAXFIELDS 1000
static int fields[MAXFIELDS] = {0};
static int* fieldp = fields;
static int fopts[MAXFIELDS] = {0};
static int* optsp = fopts;

int fieldspec(char **argv, int* flag)
{
  char* field = *argv + 1;
  /* we NEED to start with a number */
  int size = countdigits(field);

  /* Oops! No field in our first argument
   * We'll check the next one, if it exists */
  if (size <= 1 && argv + 1) {
    field = *(argv + 1);
    *flag |= NEXTED;
    size = countdigits(field);
  }

  /* Still no good? bail out */
  if (size <= 1) return NONUM;

  char* num = malloc(size);
  if (num == NULL) return BADMEM;
  char* tmp = num;
  while (isdigit(*field)) *tmp++ = *field++;
  tmp = '\0';

  *flag = 0;
  while (*field) {
    switch (*field) {
      case 'n':
        *flag |= NUMERIC;
        break;
      case 'r':
        *flag |= REVERSE;
        break;
      case 'f':
        *flag |= FOLD;
        break;
      case 'd':
        *flag |= DIRECT;
        break;
      default:
        /* Stray character found; we should stop */
        stray = *field;
        return STRAYCHAR;
        break;
    }
    ++field;
  }
  return atoi(num);
}

int main(int argc, char* argv[])
{
  int nlines, i;

  for (++argv, i = 1; i < argc; ++argv, ++i) {
    int fmag, fflag, awaitopt;
    awaitopt = fmag = fflag = 0;

    while (**argv) {
      /* Ignore args without a leading - */
      if (!awaitopt && **argv != '-') break;
      if (**argv == '-') {
        awaitopt = 1;
      }
      /* Our options */
      if (**argv == 'n') {
        options |= NUMERIC;
      }
      if (**argv == 'r') {
        options |= REVERSE;
      }
      if (**argv == 'f') {
        options |= FOLD;
      }
      if (**argv == 'd') {
        options |= DIRECT;
      }
      if (**argv == 'k') {
        options |= FIELD;
        fmag = fieldspec(argv, &fflag);
        switch (fmag) {
          case NONUM:
            printf("error: invalid field specifier\n");
            return NONUM;
            break;
          case STRAYCHAR:
            printf("error: straychar %c in field specifier\n", stray);
            return STRAYCHAR;
            break;
          case BADMEM:
            printf("error: bad memory allocation\n");
            return BADMEM;
            break;
        }
        if (fflag & NEXTED) ++argv;
        *optsp++ = fflag;
        *fieldp++ = fmag;
        break;
      }
      (*argv)++;
    }
  }

  int (*func)(void*, void*);
  if (options & NUMERIC) {
    func = (int (*)(void*, void*)) numcmp;
  } else if (options & FIELD) {
    func = (int (*)(void*, void*)) fieldcmp;
  } else {
    func = (int (*)(void*, void*)) strcmp1;
  }

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
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right)/2);
  last = left;
  /* 1 or -1 */
  for (i = left+1; i <= right; i++) {
    if ((*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsortc(v, left, last-1, comp);
  qsortc(v, last+1, right, comp);
}

int isspaceoralnum(char s)
{
  return isalnum(s) || isspace(s);
}



int strcmp1(const char *s1, const char *s2)
{
  while (*s1 && *s2 && cmp(s1, s2) == 0){
    ++s1, ++s2;
  }
  return cmp(s1, s2);
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
  while (nlines-- > 0) {
    printf("%s\n", *lineptr++);
  }
}

#define OUT 0
#define IN 1
int *cfieldp = fields;
int *cfopts = fopts;
int fieldcmp(const char *s1, const char *s2)
{
  const char *c1, *c2;
  int cmpr, word;
  cfieldp = fields;
  cfopts = fopts;

  while (*cfieldp) {
    word = OUT;
    c1 = get_field_ptr(s1, *cfieldp);
    c2 = get_field_ptr(s2, *cfieldp);
    int c;
    /* Handle the numeric switch */
    if (*cfopts & NUMERIC) {
      if ((c = numcmp(c1, c2)) == 0) {
        return c; 
      }
      ++cfieldp, ++cfopts;
      continue;
    }
    /* Handle ordinary string sort */
    while (*c1 && *c2
        && (word != IN || (!isspace(*c1) && !isspace(*c2)))
        && cmp(c1, c2) == 0) {
      if (!isspace(*c1) && !isspace(*c2)) {
        word = IN;
      }
      ++c1, ++c2;
    }
    /* If they're not the same we're done */
    if ((cmpr = cmp(c1, c2)) != 0) {
      return cmpr;
    }
    ++cfieldp, ++cfopts;
  }
  return (*cfopts & NUMERIC) ? numcmp(c1, c2) : cmp(c1, c2);
}

const char* get_field_ptr(const char *s, int fieldmax)
{
  const char *c = s;
  int word, ctr;
  word = IN;
  ctr = 1;
  /* |aa bbl cc| */
  while (ctr < fieldmax && *++c) {
    if (word == IN && isspace(*c)) {
      word = OUT;
      if (++ctr == fieldmax) {
        return c;
      }
    } else if (word == OUT && !isspace(*c)) {
      word = IN;
    }
  }
  return c;
}

int cmp(const char *s1, const char *s2)
{
  int flag = *cfopts ? *cfopts : options;
  int rev = (1 + (-2 * (flag & REVERSE)));
  if ((flag & DIRECT) && !isspaceoralnum(*s1) && !isspaceoralnum(*s2)) {
    return 0;
  }
  if (flag & FOLD) {
    return (toupper(*s1) - toupper(*s2)) * rev;
  }

  return (*s1 - *s2) * rev;
}

int numcmp(const char *s1, const char *s2)
{
  double v1, v2;
  int flag = *cfopts ? *cfopts : options;

  v1 = atof(s1);
  v2 = atof(s2);
  if (flag & REVERSE) {
    int tmp = v1;
    v1 = v2;
    v2 = tmp;
  }
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

