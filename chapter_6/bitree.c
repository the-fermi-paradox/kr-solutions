struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main()
{
  struct tnode *root;
  char word [MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      root = addtree(root, word);
    }
  }
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;
  if (p == NULL) { /* a new word has arrived */
    p = talloc(); /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++; /* repeated word */
  } else if (cond < 0) { /* less than into left subtree */
    p->left = addtree(p->left, w);
  } else { /* greater than into right subtree */
    p->right = addtree(p->right, w);
  }
  return p;
}

struct tnode *searchtree(struct tnode *p, char *w)
{
  if (p == NULL) {
    return NULL;
  }

  int cond = strcmp(w, p->word);
  if (cond < 0)
    return searchtree(p->left, w);
  else if (cond > 0)
    return searchtree(p->right, w);
  else
    return p;
}

struct tnode *iterative_searchtree(struct tnode *p, char *w)
{
  int cond;
  while (p && (cond = strcmp(w, p->word)) != 0) {
    if (cond < 0)
      p = p->left;
    else if (cond > 0)
      p = p->right;
  }
  return p;
}

struct tnode *iterative_insert(struct tnode *p, char *w)
{
  int cond;
  while (p && (cond = strcmp(w, p->word)) != 0) {
    if (cond < 0) {
      p = p->left;
    } 
    else if (cond > 0) {
      p = p->right;
    }
  }
  if (!p) {
    p = talloc();
    p->word = strdup(w);
    p->left = NULL;
    p->right = NULL;
    p->count = 0;
  }
  p->count++;
  return p;
}

void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

#include <stdlib.h>
struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s) + 1); /* +1 for \0' */
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}
