#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void push(double val);
double pop(void);
double peep(void);
int getop(char s[]);
int getch(void);
void ungetch(int c);
void dupe(void); 
double swap(void); 
void clear(void); 

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
      case '?':
        printf("\t%.8g\n", peep());
        break;
      case '!':
        clear();
        break;
      case '$':
        dupe();
        break;
      case '~':
        swap();
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
  while ((s[0] = c = getch()) == ' ' || c == '\t');
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;
  i = 0;
  if (c == '-') {
    tmp = getch();
    ungetch(tmp);
    if (!isdigit(tmp))
      return c;
  }
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = getch()));
  if (c == '.')
    while (isdigit(s[++i] = c = getch()));
  if (c != EOF) {
    ungetch(c);
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
    printf("[push] error: stack is full\n");
    return;
  }
  stack[stackp] = val; 
  ++stackp;
}

double pop(void) {
  if (!stackp) {
    printf("[pop] error: stack is empty\n");
    return 0.0;
  }
  --stackp;
  double tmp = stack[stackp];
  stack[stackp] = 0.0;
  return tmp;
}

/* Peep at the top of the stack */
double peep(void) {
  if (!stackp) {
    printf("[peep] error: stack is empty\n");
    return 0.0;
  }
  return stack[stackp - 1];
}

void dupe(void) {
  if (!stackp) {
    printf("[dupe] error: stack is empty\n");
    return;
  } 

  if (stackp >= MAXSIZE) {
    printf("[dupe] error: stack is full\n");
    return;
  }
  push(peep());
}

double swap(void) {
  if (stackp < 2) {
    printf("[swap] error: not enough elements for swap\n");
    return 0.0;
  }
  double oldtop = pop();
  double newtop = pop();
  push(oldtop);
  push(newtop);
  return newtop;
}
void clear(void) {
  stackp = 0;
}
