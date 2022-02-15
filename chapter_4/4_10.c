#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void push(double val);
double pop(void);
int getop(char s[], char line[]);
int getch(void);
void ungetch(int c);
int readline(char line[], int lim);

int pline;
#define MAXOP 100
#define NUMBER 0
int main() {
  char line[MAXOP];
  char s[MAXOP];
  int type;
  double tmp;
  while (readline(line, MAXOP) > 0) {
    pline = 0;
    while (line[pline] != '\0') {
      type = getop(s, line);
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
  }
  return 0;
}
int getop(char s[], char line[]) {
  int c;
  int i;
  while ((s[0] = c = line[pline++]) == ' ' || c == '\t');
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;
  i = 0;
  if (c == '-') {
    if (!isdigit(line[pline]))
      return c;
  }
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = line[pline++]));
  if (c == '.')
    while (isdigit(s[++i] = c = line[pline++]));
  //0123(\n)(\0)
  s[i] = '\0';
  return NUMBER;
}

int readline(char line[], int lim) {
  int c;
  int i = 0;
  while ((c = getchar()) != EOF) {
    if (i < lim - 1) {
      line[i] = c;
    }
    ++i;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  line[i] = '\0';
  return i;
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
