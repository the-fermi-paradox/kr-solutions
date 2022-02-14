#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

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
enum Command {
  ERROR = -256,
  SIN,
  COS,
  TAN,
  ASIN,
  ACOS,
  ATAN,
  SINH,
  COSH,
  TANH,
  EXP,
  SQRT,
  ABS,
  CEIL,
  FLOOR,
  LOG,
  LOGB,
  LDEXP
};

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
      case '^':
        tmp = pop();
        push(pow(pop(), tmp));
        break;
      case SIN:
        push(sin(pop()));
        break;
      case COS:
        push(cos(pop()));
        break;
      case TAN:
        push(tan(pop()));
        break;
      case ASIN:
        push(asin(pop()));
        break;
      case ACOS:
        push(acos(pop()));
        break;
      case ATAN:
        push(atan(pop()));
        break;
      case SINH:
        push(sinh(pop()));
        break;
      case COSH:
        push(cosh(pop()));
        break;
      case TANH:
        push(tanh(pop()));
        break;
      case EXP:
        push(exp(pop()));
        break;
      case SQRT:
        push(sqrt(pop()));
        break;
      case ABS:
        push(fabs(pop()));
        break;
      case CEIL:
        push(ceil(pop()));
        break;
      case FLOOR:
        push(floor(pop()));
        break;
      case LOG:
        push(log10(pop()));
        break;
      case LOGB:
        push(log2(pop()));
        break;
      case LDEXP:
        tmp = pop(); /* Power of 2 */
        push(ldexp(pop(), tmp));
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

enum Command getcmd(char cmd[]) {
  if (!strcmp("SIN", cmd)) {
    return SIN;
  }
  if (!strcmp("COS", cmd)) {
    return COS;
  }
  if (!strcmp("TAN", cmd)) {
    return TAN;
  }

  if (!strcmp("ASIN", cmd)) {
    return ASIN;
  }
  if (!strcmp("ACOS", cmd)) {
    return ACOS;
  }
  if (!strcmp("ATAN", cmd)) {
    return ATAN;
  }

  if (!strcmp("SINH", cmd)) {
    return SINH;
  }
  if (!strcmp("COSH", cmd)) {
    return COSH;
  }
  if (!strcmp("TANH", cmd)) {
    return SINH;
  }

  if (!strcmp("EXP", cmd)) {
    return EXP;
  }
  if (!strcmp("SQRT", cmd)) {
    return SQRT;
  }

  if (!strcmp("ABS", cmd)) {
    return ABS;
  }
  if (!strcmp("CEIL", cmd)) {
    return CEIL;
  }
  if (!strcmp("FLOOR", cmd)) {
    return FLOOR;
  }

  if (!strcmp("LOG", cmd)) {
    return LOG;
  }
  if (!strcmp("LOGB", cmd)) {
    return LOGB;
  }
  if (!strcmp("LDEXP", cmd)) {
    return LDEXP;
  }

  return ERROR;
}

#define MAXCMD 10
int getop(char s[]) {
  int i, c, j, tmp;
  char cmd[MAXCMD];

  while ((s[0] = c = getch()) == ' ' || c == '\t');
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-' && !isupper(c))
    return c;

  /* Commands need to be in all uppercase */
  if (isupper(c)) {
    cmd[j = 0] = c;
    while (j < MAXCMD && isupper(cmd[++j] = c = getch()));
    ungetch(c);
    cmd[j] = '\0';
    return getcmd(cmd);
  }
  if (c == '-') {
    tmp = getch();
    ungetch(tmp);
    if (!isdigit(tmp))
      return c;
  }
  i = 0;
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
