#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void push(double val);
double pop(void);
int getop(char s[]);
int getch(void);
void ungetch(int c);

#define MAXOP 100
#define NUMBER 0
int main() {
  char s[MAXOP];
  int type;
  double tmp;
  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        tmp = pop();
        push(pop() - tmp);
        break;
      case '/':
        tmp = pop();
        if (tmp == 0.0) {
          printf("error: zero divisor\n");
          return 1;
        }
        push(pop() / tmp);
        break;
      case '%':
        tmp = pop();
        if (tmp == 0) {
          printf("error: zero remainder operator\n");
          return 1;
        }
        push((int)pop() % (int)tmp);
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  return 0;
}

int getop(char s[]) {
  int c;
  int i;
  int tmp;
  static int buf = 0;
  static int bufp = 0;
  while ((s[0] = c = ((bufp) ? bufp--, buf : getchar())) == ' ' || c == '\t');
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;
  i = 0;
  if (c == '-') {
    tmp = (bufp) ? bufp--, buf : getchar();
    buf = tmp;
    bufp++;
    if (!isdigit(tmp))
      return c;
  }
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = ((bufp) ? bufp--, buf : getchar())));
  if (c == '.')
    while (isdigit(s[++i] = c = ((bufp) ? bufp--, buf : getchar())));
  if (c != EOF) {
    buf = c;
    bufp++;
  }
  s[i] = '\0';
  return NUMBER;
}

/* getch and ungetch */
#define MAXBUF 100
int bufp;
int buf[MAXBUF];

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= MAXBUF) {
    printf("error: buf size exceeded\n");
    return;
  }
  buf[bufp++] = c;
}

/* Stack Implementation */
#define MAXSIZE 100
int stackp; /* Stack counter */
double stack[MAXSIZE];

void push(double val) {
  if (stackp >= MAXSIZE) {
    printf("error: stack is full\n");
    return;
  }
  stack[stackp] = val; 
  ++stackp;
}

double pop(void) {
  if (!stackp) {
    printf("error: stack is empty\n");
    return 0.0;
  }
  --stackp;
  double tmp = stack[stackp];
  stack[stackp] = 0.0;
  return tmp;
}
