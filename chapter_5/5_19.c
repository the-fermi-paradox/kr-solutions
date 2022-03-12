#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define OK 0
#define ERROR -1

enum { NAME, PARENS, BRACKETS };

int  getch(void);
void ungetch(int c);
int  gettoken(void);
int  tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char lasttoken[MAXTOKEN];
char out[1000]; /* our output string */

/* gettoken modifies the contents of token and tokentype */
int gettoken(void)
{
  int c;
  char *p = token;

  /* store the last token in the lasttoken */
  strcpy(lasttoken, token);
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

int  stack[MAXTOKEN];
int  stackp;

#define MAXTEMP 1101
int main()
{
  int type, last;
  char temp[MAXTEMP];
  while (gettoken() != EOF) {
    strcpy(out, token);
    last = 0;
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
        if (last == '*') {
          sprintf(temp, "(%s)%s", out, token);
          strcpy(out, temp);
        } else {
          strcat(out, token);
        }
      }
      else if (type == '*') {
        sprintf(temp, "*%s", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else {
        printf("invalid input at %s\n", token);
      }
      printf("%s '%c'\n", out, last);
      last = type;
    }
    printf("%s\n", out);
  }
  return 0;
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
