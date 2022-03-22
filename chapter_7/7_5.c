#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int getch(void);
void ungetch(int c);
void push(double val);
int getop (char *s, char *line, int *pnt);
double pop(void);
int readline(char *line, int lim);
#define NUMBER -1
#define MAXOP 1000
int main() {
  char line[MAXOP];
  char s[MAXOP];
  int type, pline;
  double tmp;
  while (readline(line, MAXOP) > 0) {
    pline = 0;
    while (line[pline] != '\0') {
      type = getop(s, line, &pline);
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
          printf("type: %c(%d)\n", type, type);
          printf("error: unknown command %s\n", s);
          break;
      }
    }
  }
  return 0;
}

int getop (char *s, char *line, int *pnt)
{
  double num = 0;
  int offset = 0;
  if(sscanf(line + *pnt, "%lf%n", &num, &offset) == 1) {
    sprintf(s, "%lf", num);
    *pnt += offset;
    return NUMBER; 
  } else if(sscanf(line + *pnt, "%1s%n", s, &offset) == 1) {
    *pnt += offset;
    return *s; 
  } else {
    (*pnt)++;
    return '\n';
  }
}

int readline(char *line, int lim)
{
  char *s = line;
  int c;
  while ((c = getch()) != EOF) {
    *s++ = c;
    if (c == '\n') {
      break;
    }
    if (s - line >= lim - 1) {
      break;
    }
  }
  if (s == line) {
    return 0;
  }
  *s = '\0';
  return s - line;
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
