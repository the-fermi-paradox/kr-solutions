#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct nlist { /* table entry */
  struct nlist *next; /* next entry in linked list */
  char *name;
  char *defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /*pointer table */

unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *parent;

/*lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)], parent = NULL; np != NULL; parent = np, np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np;
    }
  }
  return NULL;
}

struct nlist *lookup(char *);
char *strgup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { /* not found */
    np = malloc(sizeof(*np));
    if (np == NULL || (np->name = strgup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free(np->defn);
  }
  if ((np->defn = strgup(defn)) == NULL) {
    return NULL;
  }
  return np;
}

void undef(char* name)
{
  struct nlist *toremove = lookup(name);
  if (parent)
    parent->next = toremove->next;
  else if (!parent && toremove->next)
    hashtab[hash(name)] = toremove->next;
    

  free(toremove->name);
  free(toremove->defn);
  free(toremove);
}

char *strgup(char *s)
{
  char* p = malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

int main()
{
  install("word", "this is a definition");
  install("bird", "this is a definition");
  install("third", "this is a definition");
  install("jird", "nerd");
  undef("third");
  struct nlist *np = lookup("third");
  printf("third: ");
  printf(np ? "not null" : "null");
  printf("\n");
  np = lookup("bird");
  printf("bird: ");
  printf(np ? "not null" : "null");
  printf("\n");
  np = lookup("jird");
  printf("jird: ");
  printf(np ? "not null" : "null");
  printf("\n");
}
