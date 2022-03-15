#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
struct group {
  char* key;
  struct treenode* root;
  struct group* left;
  struct group* right;
};

struct treenode {
  char* word;
  struct treenode* left;
  struct treenode* right;
};

int getch(void);
void ungetch(int);
char *strgup(char *s);
int groupsize;

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

char* extractgroup(char* g)
{
  char* copy = malloc(groupsize + 1);
  char* src = copy;
  int i = 0;
  while (*g && i < groupsize) {
    *copy++ = *g++;
    ++i;
  }
  copy = '\0';
  return src;
}

struct treenode* addnode(struct treenode* tn, char* word)
{
  struct treenode* lstptr = NULL;
  while(tn) {
    lstptr = tn;
    if (strcmp(word, tn->word) < 0) {
      tn = tn->left;
    } else {
      tn = tn->right;
    }
  }
  tn = malloc(sizeof(struct treenode));
  tn->word  = strgup(word);
  tn->left  = NULL;
  tn->right = NULL;
  if (lstptr) {
    if (strcmp(word, lstptr->word) < 0) {
      lstptr->left = tn;
    } else {
      lstptr->right = tn;
    }
  }
  return tn;
}

struct group* addgroup(struct group* root, char* word)
{
  struct group* grp = root;
  char* key = extractgroup(word);
  struct group* lstptr = NULL;
  int cond;
  while(grp && (cond = strcmp(key, grp->key)) != 0) {
    lstptr = grp;
    if (cond < 0) {
      grp = grp->left;
    } else if (cond > 0) {
      grp = grp->right;
    }
  }
  if (grp == NULL) {
    grp        = malloc(sizeof(struct group));
    grp->key   = key;
    grp->left  = NULL;
    grp->right = NULL;
    grp->root  = NULL;
  }
  if (grp->root == NULL) {
    grp->root = addnode(grp->root, word);
  } else {
    addnode(grp->root, word);
  }
  if (lstptr) {
    if ((cond = strcmp(key, lstptr->key)) < 0) {
      lstptr->left = grp;
    } else if (cond > 0) {
      lstptr->right = grp;
    }
  }
  return root ? root : grp;
}

void traversetree(struct treenode* tn)
{
  if (tn == NULL)
    return;
  traversetree(tn->left);
  printf("%s\n", tn->word);
  traversetree(tn->right);
}

void traversegroup(struct group* grp)
{
  if (grp == NULL)
    return;
  traversegroup(grp->left);
  printf("\n%s\n", grp->key);
  printf("----------\n");
  traversetree(grp->root);
  traversegroup(grp->right);
}

int main(int argc, char** argv)
{
#define DEFAULT 6
  groupsize = argc >= 2 ? atoi(argv[1]) : DEFAULT;
  groupsize = groupsize ? groupsize : DEFAULT;

#define MAXWORD 100
  char word[MAXWORD];
  struct group* root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (strlen(word) > groupsize) {
      root = addgroup(root, word);
    }
  }
  traversegroup(root);
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

char *strgup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s) + 1); /* +1 for \0' */
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}
