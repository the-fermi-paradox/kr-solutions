#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100
#define MAXTEMP 1130
#define OK 0
#define ERROR -1

enum { NAME, PARENS, BRACKETS, CONST};
int dcl(void);
int dirdcl(void);
void print(void);
void nextline(void);

int  getch(void);
void ungetch(int c);
int  gettoken(void);
int  tokentype;
int  hasname;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000]; /* our output string */

/* gettoken modifies the contents of token and tokentype */
int gettoken(void)
{
  int c;
  char *p = token;

  /* skip leading blanks */
  while ((c = getch()) == ' ' || c == '\t')
    ;
  /* if parens */
  if (c == '(') {
    /* if parens is immediately matched by a closing parens */
    if (hasname) {
      int j;
      for (*p++ = c; (j = (*p++ = getch())) != ')';) {
        if (j == '\n') {
          ungetch(j);
          return '\n';
        }
      }
      *p = '\0';

      return tokentype = PARENS;
    } else {
      return tokentype = '(';
    }
    /* if bracket opened */
  } else if (c == '[') {
    /* store contents inside brackets in token */
    for (*p++ = c; (*p++ = getch()) != ']';);
    *p = '\0';

    /* return the brackets */
    return tokentype = BRACKETS;
    /* if letter */
  } else if (isalpha(c)) {
    /* store all sequential letters in token */
    for (*p++ = c; isalnum(c = getch());) {
      *p++ = c;
    }
    *p = '\0';
    ungetch(c);
    /* return special name flag */
    return strcmp(token, "const") ? (tokentype = NAME) : (tokentype = CONST);
  } else {
    /* just return the value */
    return tokentype = c;
  }
}

int dcl(void)
{
  #define MAXPNTRS 500
  #define CONST_PNTR " const pointer to"
  #define PNTR       " pointer to" 
  int ret, c;
  char *arr[MAXPNTRS] = {NULL};
  char **p = arr;
  /* Count the asterisks while calling get token */
  while (gettoken() == '*') {
    c = gettoken();
    if (c == CONST) {
      *p = malloc(sizeof(CONST_PNTR));
      strcpy(*p, CONST_PNTR); 
    } else {
      *p = malloc(sizeof(PNTR));
      strcpy(*p, PNTR); 
      ungetch(c);
    }
    ++p;
  }

  /* We'll have called gettoken() one time over the number of
   * asterisks; dirdcl works with that gettoken */
  if ((ret = dirdcl()) != OK) {
    return ret;
  }

  while (--p >= arr) {
    strcat(out, *p);
    free(*p);
  }
  return OK;
}

int dirdcl(void)
{
  int type, ret;

  /* token type is a global variable set from gettoken() */
  if (tokentype == '(') {
    if ((ret = dcl()) != OK) {
      return ret;
    }
    if (tokentype != ')') {
      printf("error: missing )\n");
      return ERROR;
    }
  } else if (tokentype == NAME) {
    hasname = 1;
    strcpy(name, token);
  } else {
    printf("error: expected name or (dcl)\n");
    return ERROR;
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      if (strcmp(token, "()")) {
        char temp[MAXTEMP];
        sprintf(temp, "%s function %s returning", out, token);
        strcpy(out, temp);
      } else {
        strcat(out, " function returning");
      }
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
  return OK;
}

int  stack[MAXTOKEN];
int  stackp;

int validate(char *val)
{
  char* valid_types[] = {
    "const",
    "int",
    "char",
    "float",
    "double",
    NULL
  };
  char** p;
  for (p = valid_types; *p != NULL; ++p) {
    if (strcmp(*p, val) == 0) {
      return 1;
    }
  }
  return 0;
}

int main()
{
  int v, i;
  i = 0;
  /* while our token isnt eof */
  for (printf("decl> "); (v = gettoken()) != EOF; printf("decl> ")) {
    hasname = 0;
    if (i == 0 && v == '\n') {
      printf("error: empty input\n");
      continue;
    }

    if (!validate(token)) {
      printf("error: invalid type\n");
      nextline();
      continue;
    }
    strcpy(datatype, token);
    /* If a leading const we need to handle it! */
    if (v == CONST) {
      v = gettoken();
      if (v == '\n') {
        printf("error: expected name or (dcl)");
        continue;
      } else if (!validate(token)) {
        printf("error: invalid type\n");
        nextline();
        continue;
      }
      sprintf(datatype, "%s %s", datatype, token);
    } 
    out[0] = '\0';

    if (dcl() != OK) {
      if (v != '\n' && tokentype != '\n') {
        nextline();
      }
      i = -1;
    } else if (tokentype != '\n') {
      printf("syntax error\n");
      nextline();
      i = -1;
    } else {
      printf("%s: %s %s\n", name, out, datatype);
      i = -1;
    }
    ++i;
  }
  return 0;
}

void nextline(void)
{
	int c;

	while ((c = getch()) != '\n' && c != EOF)
		;
	if (c == EOF)
		ungetch(c);
}

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
