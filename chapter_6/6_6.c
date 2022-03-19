#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct nlist { /* table entry */
  struct nlist *next; /* next entry in linked list */
  char *name;
  char *defn;
};

/* Hash table */
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char* name);
char *strgup(char *);

/* word getting stack */
int getword(char *word, int lim);
char* readline(int lim);
void ungetch(int c);
int getch(void);

#define MAXWORD 1000
#define MAXLINES 20000

char* removecomments(char* line, int* stt)
{
  char tmp[MAXWORD];
  char* linep = line;
  char* tmpp = tmp;
  /* two types of comments:
   * C89 and C99
   * One goes until it meets a delimeter
   * The other just takes up the line
   * We need to remove both
   */
  #define NO_COMMENT    0
  #define STAR_COMMENT  1
  while (*linep) {
    if (*linep == '/' && *(linep + 1) == '/') {
      break;
    }
    if (*linep == '/' && *(linep + 1) == '*') {
      *stt = STAR_COMMENT;
    }
    
    if ((*stt)) {
      if (*linep == '*' && *(linep + 1) == '/') {
        *stt = NO_COMMENT; 
        linep++;
      }
      linep++;
    } else {
      *tmpp++ = *linep++;
    }
  }
  *tmpp = '\0';
  return strgup(tmp);
}

#define NL    0
#define SPACE 1
char* getwrd(char* pnt, char** newp, int limit)
{
  char  tmpword[MAXWORD];
  char* tmpwordp = tmpword;
  if (*pnt == '\0') {
    return NULL;
  }
  /* Skip leading whitespace */
  while (isspace(*pnt)) {
    *tmpwordp++ = *pnt++;
  }
  /* If we incremented pnt,
   * return a chunk of spaces as a 'word' */
  if (*pnt != **newp) {
    *newp = pnt;
    *tmpwordp = '\0';
    return strgup(tmpword);
  }

  if (!isalpha(*pnt) && limit != NL) {
    *tmpwordp++ = *pnt++;
    *newp = pnt;
    *tmpwordp = '\0';
    return strgup(tmpword);
  }

  int i;
  switch (limit) {
  case NL:
    i = 0;
    while (*pnt != '\n') {
      *tmpwordp++ = *pnt++;
      ++i;
    }
    break;
  case SPACE:
    i = 0;
    while (isalpha(*pnt) && !isspace(*pnt)) {
      *tmpwordp++ = *pnt++;
      ++i;
    }
    break;
  default:
    printf("ERROR\n");
    return NULL;
  }
  *tmpwordp = '\0';
  *newp = pnt;
  return strgup(tmpword);
}

char* preprocess(char* line)
{
  const char* keyword = "define";
  char* pnt = line;  

  /* Skip leading whitespace */
  while (*pnt && isspace(*pnt)) {
    ++pnt;
  }
  /* Preprocessor directive */
  if (*pnt == '#') {
    int i;
    /* Check if we have a valid define directive */
    for (i = 0, ++pnt; i < strlen(keyword); ++i) {
      /* Not valid */
      if (*pnt++ != keyword[i]) {
        return line;
      }
    }
    /* Store and free our results */
    while (isspace(*pnt)) ++pnt;
    char* name = getwrd(pnt, &pnt, SPACE);
    while (isspace(*pnt)) ++pnt;
    char* def = getwrd(pnt, &pnt, NL);
    install(name, def);
    free(name);
    free(def);
    /* Delete line now that we're done */
    *line = '\0';
  }
  return line;
}

int main()
{
  char* lines[MAXLINES] = {NULL};
  char** linep = lines;
  char* newline = NULL;
  char* p = NULL;
  int state = 0;
  int oldmem = 0;

  /* Read all the lines */
  while ((p = readline(MAXWORD))) {
    *linep++ = p; 
  }
  for (linep = lines; *linep; ++linep) {
    /* Strip out comments */
    *linep = removecomments(*linep, &state);
    /* extract defines */
    *linep = preprocess(*linep);

    /* Now find and replace */
    oldmem = strlen(*linep) + 1;
    newline = malloc(oldmem);
    *newline = '\0';
    while ((p = getwrd(*linep, linep, SPACE))) {
      struct nlist* nl;
      if ((nl = lookup(p))) {
        /* Make space for our replacement word */
        newline = realloc(newline, (oldmem = (oldmem - strlen(nl->name) + strlen(nl->defn))));
        p = nl->defn;
      }
      strcat(newline, p);
    }
    *linep = newline;
    printf("%s", *linep);
  }

  return 0;
  goto error;
  error: {
    printf("ERROR: malformed define statement. aborting.\n");
    return -1;
  }
}

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
  if (s == NULL) {
    return NULL;
  }
  char* p = malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

char* readline(int lim)
{
  char tmp[lim];
  int c, i;
  i = 0;
  while ((c = getch()) != EOF) {
    if (i >= lim - 1) {
      break;
    }
    tmp[i++] = c;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return NULL;
  }
  tmp[i] = '\0';
  return strgup(tmp);
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
#define x 1000
int y = x + x;
