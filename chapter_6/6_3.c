#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
  char* word;
  char* lines;
  struct tnode* left;
  struct tnode* right;
};

int  getword(char *word, int lim);
int  getch(void);
void ungetch(int);
char* itoa(int i);
char* strgup(char *s);

int linenum = 1;

struct tnode* addnode(struct tnode* tn, char* word)
{
  struct tnode* lastnode = NULL;
  int cond;
  while (tn && (cond = strcmp(word, tn->word)) != 0) {
    lastnode = tn;
    if (cond < 0) {
      tn = tn->left;
    } else {
      tn = tn->right;
    }
  }
  char* currline = itoa(linenum);
  /* initialize our node */
  if (tn == NULL) {
    tn = malloc(sizeof(struct tnode));
    tn->left   = NULL;
    tn->right  = NULL;
    tn->word   = strgup(word);
    tn->lines  = currline; 
  } /* otherwise one already exists, let's append the line this word is on to it */
  else if (cond == 0) { 
    /* 3 = one for comma, one for space, one for \0 */
    char* tmp = malloc(strlen(tn->lines) + strlen(currline) + 3);
    sprintf(tmp, "%s, %s", tn->lines, currline);
    tn->lines = tmp;
    /* we can release currline because its data lives in tmp now */
    free(currline);
  }

  if (lastnode) {
    if ((cond = strcmp(word, lastnode->word)) < 0) {
      lastnode->left = tn;
    } else {
      lastnode->right = tn;
    }
  }
  return tn;
}

/* traverse a tree, printing output along the way */
void traverse(struct tnode* tn)
{
  if (tn == NULL) {
    return;
  }
  traverse(tn->left);
  printf("%s | %s\n", tn->word, tn->lines);
  traverse(tn->right);
}

/* determine whether we should skip the word or not */
int isignore(char* word)
{
  char* ignore_words[] = {
    "the",
    "to",
    "from",
    "of",
    "and",
    "if",
  };
  int i;
  for (i = 0; i < sizeof(ignore_words) / sizeof(ignore_words[0]); ++i) {
    if (strcmp(word, ignore_words[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

int main(void)
{
#define MAXWORD 100
  char word[MAXWORD];
  struct tnode* root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (strlen(word) < 2) {
      continue;
    }
    if (isignore(word)) {
      continue;
    }
    if (root == NULL) {
      root = addnode(root, word);
    } else {
      addnode(root, word);
    }
  }
  traverse(root);
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
