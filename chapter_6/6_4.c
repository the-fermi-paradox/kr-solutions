#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* TODO: Reimplement this using a Set, which is the perfect datastructure for the problem.
 * Unfortunately we haven't covered hash tables yet. */
struct wordnode {
  char* word;
  int count;
};

int  getword(char *word, int lim);
int  getch(void);
void ungetch(int);
char* itoa(int i);
char* strgup(char *s);
void qzort(struct wordnode** x, int left, int right);

int linenum = 1;

struct wordnode** addnode(struct wordnode** xp, struct wordnode* wn)
{
  *xp++ = wn;  
  return xp;
}

/* Returns the position of word in the array, if it exists */
#define NONE -1
int contains(struct wordnode** x, char* word)
{
  struct wordnode** xp = x;
  while (xp && *xp) {
    if (strcmp(word, (*xp)->word) == 0) {
      return xp - x;
    }
    ++xp;
  }
  return NONE;
}

void increment(struct wordnode** x, int pos)
{
  ((x[pos])->count)++; 
}

struct wordnode* createwordnode(char *word)
{
  struct wordnode* wn;
  wn = malloc(sizeof(struct wordnode));
  wn->word  = strgup(word);
  wn->count = 1;
  return wn;
}

int main(void)
{
  #define MAXWORDS 5000
  #define MAXWORD 100
  struct wordnode* x[MAXWORDS] = {0};
  struct wordnode** xp = x;
  char word[MAXWORD];
  while (getword(word, MAXWORD) != EOF) {
    if (strlen(word) < 2) {
      continue;
    }
    int i;
    if ((i = contains(x, word)) != NONE) {
      increment(x, i);
    } else {
      struct wordnode* wn = createwordnode(word);
      xp = addnode(xp, wn);
    }
  }
  qzort(x, 0, xp - x - 1);
  while(--xp >= x) {
    printf("%d %s\n", (*xp)->count, (*xp)->word);
  }
}

#define STACKMAX 100
#define ERROR    -1
char  stack[STACKMAX];
char* stackp = stack;

void push(char x)
{
  if (stackp - stack >= STACKMAX) {
    printf("stack full\n");
    return;
  }
  *stackp++ = x;
}

char pop(void)
{
  if (stackp == stack) {
    return ERROR;
  }
  return *--stackp;
}

char* itoa(int i)
{
  while (i) {
    push(i % 10 + '0');
    i /= 10;
  }
  char *str = malloc(sizeof(stack) + 1);
  char *walk = str;
  int c;

  while ((c = pop()) != ERROR) {
    *walk++ = c;
  }
  *walk = '\0';
  return str;
}

void nextline()
{
  int c;
  while ((c = getch()) != '\n' && c != EOF);
  if (c == '\n') linenum++;
  if (c == EOF) ungetch(c);
}

void nextquote()
{
  int c;
  while ((c = getch()) != '"' && c != EOF && c != '\n');
  if (c == '\n') linenum++;
  if (c == EOF) ungetch(c);
}

void nextclose()
{
  int c, tmp;
  while ((c = getch()) != EOF) {
    if (c == '\n') linenum++;
    if (c == '*') {
      tmp = getch();
      if (tmp == '/') {
        return;
      } else {
        ungetch(tmp);
      }
    }
  }
  if (c == EOF) {
    ungetch(c);
  }
}


int getword(char *word, int lim)
{
  int c, tmp;
  char *w = word;

  while (isspace(c = getch())) {
    if (c == '\n') linenum++;
  }
  if (c != EOF) {
    *w++ = c;
  }
  
  /* Handle C comments */
  if (c == '/') {
    tmp = getch();
    if (tmp == '*') {
      nextclose();
    } else {
      ungetch(tmp);
    }
  }

  /* Handle C++ comments */
  if (c == '/') {
    tmp = getch();
    if (tmp == '/') {
      nextline();
    } else {
      ungetch(tmp);
    }
  }

  /* Handle string literals */
  if (c == '"') {
    nextquote();
  }

  /* Handle preprocessor control lines */
  if (c == '#') {
    nextline();
  }

  if (!isalpha(c) && c != '_') {
    *w = '\0';
    return c;
  }

  for (; --lim > 0; w++) {
    if (!isalnum(*w = getch()) && *w != '_') {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

#define MAXTOKEN 1000
static int getstack[MAXTOKEN];
static int getstackp;

int getch(void)
{
  return getstackp > 0 ? getstack[--getstackp] : getchar();
}

void ungetch(int c)
{
  if (getstackp >= MAXTOKEN - 1) {
    printf("error: stack full\n");
    return;
  }
  getstack[getstackp++] = c;
}

char* strgup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s) + 1); /* +1 for \0' */
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

void swap(struct wordnode** x, int i, int j);

void qzort(struct wordnode** a, int left, int right) {
  if (left >= right) {
    return;
  }
  int pivp = (right + left) / 2;
  struct wordnode* piv = a[pivp];
  int i = left;
  int j = right;
  while (i <= j) {
    while (a[i]->count < piv->count) {
      ++i;
    }
    while (a[j]->count > piv->count) {
      --j;
    }
    if (i <= j) {
      swap(a, i, j);
      ++i;
      --j;
    }
  }
  qzort(a, left, i - 1);
  qzort(a, i, right);
}

void swap(struct wordnode** x, int i, int j)
{
  struct wordnode* tmp;
  tmp = x[j];
  x[j] = x[i];
  x[i] = tmp;
}
