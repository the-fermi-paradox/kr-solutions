#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
static void push(double n);
static double pop(void);
static void prints(void);
int main(int argc, char* argv[])
{
  char** p = argv + 1;
  double tmp, intpart;
  int l;
  while (p - argv < argc){
    if (isdigit(**p) || ((**p == '-' || **p == '+') && isdigit(*(*p + 1)))) {
      push(atof(*p) * ((**p == '-') ? -1 : 1));
    } 

    /* basic operators */
    else if (**p == '+') {
      push(pop() + pop());
    } 
    else if (**p == '-') {
      tmp = pop();
      push(pop() - tmp);
    } 
    else if (**p == '*') {
      push(pop() * pop());
    } 
    else if (**p == '/') {
      tmp = pop();
      push(pop() / tmp);
    }
    else if (**p == '%') {
      tmp = pop();
      push((int)pop() % (int)tmp);
    }
    else if (**p == '^') {
      tmp = pop();
      pow(pop(), tmp);
    }

    /* rounding */
    else if (strcmp(*p, "ceil") == 0) {
      push(ceil(pop()));
    }
    else if (strcmp(*p, "floor") == 0) {
      push(floor(pop()));
    }
    else if (strcmp(*p, "round") == 0) {
      push(round(pop()));
    }
    else if (strcmp(*p, "abs") == 0) {
      push(fabs(pop()));
    }

    /* roots */
    else if (strcmp(*p, "sqrt") == 0) {
      push(sqrt(pop()));
    }
    else if (strcmp(*p, "cbrt") == 0) {
      push(cbrt(pop()));
    }
    else if (strcmp(*p, "hypot") == 0) {
      push(hypot(pop(), pop()));
    }

    /* logs */
    else if (strcmp(*p, "ln") == 0) {
      push(log(pop()));
    }
    else if (strcmp(*p, "log10") == 0) {
      push(log10(pop()));
    }
    else if (strcmp(*p, "log2") == 0) {
      push(log2(pop()));
    }


    /* exponentals */
    else if (strcmp(*p, "exp") == 0) {
      push(exp(pop()));
    }
    else if (strcmp(*p, "ldexp") == 0) {
      tmp = pop();
      push(ldexp(pop(), tmp));
    }
    else if (strcmp(*p, "exp2") == 0) {
      push(exp2(pop()));
    }

    /* floating point stuff */
    /* extract mantissa */
    else if (strcmp(*p, "exmant") == 0) {
      push(frexp(pop(), &l));
    }
    /* extract exponent */
    else if (strcmp(*p, "exexp") == 0) {
      frexp(pop(), &l);
      push(l);
    }
    /* extract integer */
    else if (strcmp(*p, "exint") == 0) {
      modf(pop(), &intpart);
      push(intpart);
    }
    /* extract decimal */
    else if (strcmp(*p, "exdec") == 0) {
      push(modf(pop(), &intpart));
    }

    /* trigonometric functions */
    else if (strcmp(*p, "sin") == 0) {
      push(sin(pop()));
    }
    else if (strcmp(*p, "cos") == 0) {
      push(cos(pop()));
    }
    else if (strcmp(*p, "tan") == 0) {
      push(tan(pop()));
    }
    else if (strcmp(*p, "asin") == 0) {
      push(asin(pop()));
    }
    else if (strcmp(*p, "acos") == 0) {
      push(acos(pop()));
    }
    else if (strcmp(*p, "atan") == 0) {
      push(atan(pop()));
    }
    else if (strcmp(*p, "sinh") == 0) {
      push(sinh(pop()));
    }
    else if (strcmp(*p, "cosh") == 0) {
      push(cosh(pop()));
    }
    else if (strcmp(*p, "tanh") == 0) {
      push(tanh(pop()));
    }
    else if (strcmp(*p, "asinh") == 0) {
      push(asinh(pop()));
    }
    else if (strcmp(*p, "acosh") == 0) {
      push(acosh(pop()));
    }
    else if (strcmp(*p, "atanh") == 0) {
      push(atanh(pop()));
    }

    else if (**p == 'p') {
      printf("%g", pop());
    }
    p++;
  }
  printf("%g", pop());
}

#define STACKSIZE 1000
static double stack[STACKSIZE];
static double* stackp = stack;

static void prints(void)
{
  double* p = stack;
  printf("stack: [");
  while (p < stackp - 1) {
    printf("%g, ", *p);
    ++p;
  }
  printf("%g]\n", *p);
}

static void push(double n)
{
  if (stackp - stack < STACKSIZE) {
    *stackp++ = n;
  } else {
    printf("stack overflow");
  }
  prints();
}

static double pop(void)
{
  if (stackp == stack) {
    printf("error: stack empty");
    return 0;
  }

  return *--stackp;
}
