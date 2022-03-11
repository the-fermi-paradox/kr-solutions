#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define OK 0
#define ERROR -1

enum { NAME, PARENS, BRACKETS };
int dcl(void);
int dirdcl(void);
void print(void);
void nextline(void);

int  getch(void);
void ungetch(int c);
int  gettoken(void);
int  tokentype;
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
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
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
      *p++ =c;
    }
    *p = '\0';
    ungetch(c);
    /* return special name flag */
    return tokentype = NAME;
  } else {
    /* just return the value */
    return tokentype = c;
  }
}

int dcl(void)
{
  int ns, ret;
  /* Count the asterisks while calling get token */
  for (ns = 0; gettoken() == '*';) {
    ns++;
  }
  /* We'll have called gettoken() one time over the number of
   * asterisks; dirdcl works with that gettoken */
  if ((ret = dirdcl()) != OK) {
    return ret;
  }
  while (ns-- > 0) {
    strcat(out, " pointer to");
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
    strcpy(name, token);
  } else {
    printf("error: expected name or (dcl)\n");
    return ERROR;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
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

int main()
{
  int v, i;
  i = 0;
  /* while our token isnt eof */
  while ((v = gettoken()) != EOF) {
    if (i == 0 && v == '\n') {
      printf("error: empty input\n");
      continue;
    }
    /* copy the token into the datatype */
    strcpy(datatype, token);
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

void print(void)
{
  int i = 0;
  printf("stack:\t\t");
  printf("[");
  while (i < stackp) {
    printf("%d, ", stack[i++]);
  }
  printf("]\n");

  printf("tokentype:\t%d\n", tokentype);
  printf("token:\t\t%s\n", token);
  printf("name:\t\t%s\n", name);
  printf("datatype:\t%s\n", datatype);
  printf("output:\t\t%s\n", out); /* our output string */
  printf("-----------\n");
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
