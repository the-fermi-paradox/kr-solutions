#include <stdio.h>
#include <string.h>
#include <ctype.h>
struct key {
  char *word;
  int count;
} keytab[] = {
  {"auto", 0},
  {"break", 0},
  {"case", 0},
  {"char", 0},
  {"const", 0},
  {"continue", 0},
  {"default", 0},
  {"do", 0},
  {"double", 0},
  {"else", 0},
  {"enum", 0},
  {"extern", 0},
  {"float", 0},
  {"for", 0},
  {"goto", 0},
  {"if", 0},
  {"int", 0},
  {"long", 0},
  {"register", 0},
  {"return", 0},
  {"short", 0},
  {"signed", 0},
  {"sizeof", 0},
  {"static", 0},
  {"struct", 0},
  {"switch", 0},
  {"typedef", 0},
  {"union", 0},
  {"unsigned", 0},
  {"void", 0},
  {"volatile", 0},
  {"while", 0},
};
int getch(void);
void ungetch(int);
#define NKEYS sizeof(keytab) / sizeof(keytab[0])
struct key * binsearch(char *word, int start, int end)
{
  if (end < start) {
    return NULL;
  }

  int div = (end + start) / 2;

  struct key *p = keytab + div;
  int cmp = strcmp(word, p->word);
  if (cmp < 0) {
    return binsearch(word, start, div - 1);
  } else if (cmp > 0) {
    return binsearch(word, div + 1, end);
  }
  return p;
}

void nextline()
{
  int c;
  while ((c = getch()) != '\n' && c != EOF);
  if (c == EOF) ungetch(c);
}

void nextquote()
{
  int c;
  while ((c = getch()) != '"' && c != EOF && c != '\n');
  if (c == EOF) ungetch(c);
}

void nextclose()
{
  int c, tmp;
  while ((c = getch()) != EOF) {
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

  while (isspace(c = getch()));
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

int main()
{
#define MAXWORD 100
  struct key *n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      if ((n = binsearch(word, 0, NKEYS - 1)) != NULL) {
        (n->count)++;
      }
    }
  }
  int i;
  for (i = 0; i < NKEYS; i++) {
    if (keytab[i].count > 0)
      printf("%4d %s\n",
          keytab[i].count, keytab[i].word);
  }
  return 0;
}

#define MAXTOKEN 1000
static int stack[MAXTOKEN];
static int stackp;

int getch(void)
{
  return stackp > 0 ? stack[--stackp] : getchar();
}

void ungetch(int c)
{
  if (stackp >= MAXTOKEN - 1) {
    printf("error: stack full\n");
    return;
  }
  stack[stackp++] = c;
}

