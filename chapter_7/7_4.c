#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
int getch(void);
void ungetch(int c);

#define NUMCAP 5000
int numstack[NUMCAP];
int *numstackp = numstack;
void push(int n)
{
  if (numstackp - numstack >= NUMCAP) {
    printf("error: numstack full\n");
    return;
  }
  *numstackp++ = n;
}

#define EMPTY -1
int pop(void)
{
  if (numstackp == numstack) {
    return EMPTY;
  }
  return *--numstackp;
}

long int stdin_toi(int c, int base)
{
  numstackp = numstack;
  long int num, k;
  char i;
  char sign = 1;
  num = i = 0;
  k = 1;
  if (c == '-') {
    sign = -1;
    c = getch();
  }
  for (; isdigit(c) || (base == 16 && c >= 'A' && c <= 'F'); c = getch()) {
    if (base == 16 && c >= 'A' && c <= 'F') {
      push(c - 55);
    } else {
      push(c - '0');
    }
  }
  ungetch(c);
  while ((i = pop()) != EMPTY) {
    num += (i * k);
    k *= base;
  }
  return num * sign;
}

void minscanf(char *fmt, ...)
{ 
  va_list ap;
  char *p;
  char islong = 0;
  int c;

  va_start(ap, fmt);
  for(p = fmt; *p; p++) {
    while (isspace(*p)) ++p;
    while (isspace((c = getch())));
    
    if (*p != '%') {
      if (c != *p) return;
      continue;
    }
    /* Build special string */
    do {
      if (*p == 'l')
        islong++;
      p++;
    } while(*p && !isspace(*p) && *p != 'x' && *p != 'd' && *p != 'i' && 
        *p != 'o' && *p != 'c' && *p != 'u' && *p != 'f' && *p != 's');
    int num;
    #define MAXSTR 100
    char str[MAXSTR];
    char *strp = str;

    switch (*p) {
    case 'd': /* Fallthrough */
    case 'i':
      num = stdin_toi(c, 10);
      if (islong)
        *va_arg(ap, long int*) = num;
      else
        *va_arg(ap, int*) = num;
      break;
    case 'o':
      num = stdin_toi(c, 8);
      if (islong)
        *va_arg(ap, long int*) = num;
      else
        *va_arg(ap, int*) = num;
      break;

    case 'x':
      if (c == '0') {
        c = getch();
        if (c == 'x' || c == 'X') {
          c = getch();
        }
      }
      num = stdin_toi(c, 16);
      if (islong)
        *va_arg(ap, long int*) = num;
      else
        *va_arg(ap, int*) = num;
      break;
    case 'u':
      num = stdin_toi(c, 10);
      if (islong)
        *va_arg(ap, long unsigned int*) = num;
      else
        *va_arg(ap, unsigned int*) = num;
      break;
    case 'c':
      *va_arg(ap, char*) = c;
      break;
    case 'f':
      if (c == '-' || c == '+') {
        *strp++ = c;
        c = getch();
      }
      while (isdigit(c)) {
        *strp++ = c; 
        c = getch();
      }

      if (c == '.') {
        *strp++ = c;
        c = getch();
      }

      while (isdigit(c)) {
        *strp++ = c;
        c = getch();
      }
      *strp = '\0';
      ungetch(c);
      if (islong)
        *va_arg(ap, double*) = strtod(str, NULL);
      else
        *va_arg(ap, float*) = strtof(str, NULL);
      break;
    case 's':
      while (!isspace(c)) {
        *strp++ = c;
        c = getch();
      }
      *strp = '\0';
      strcpy(va_arg(ap, char*), str);
      break;
    default:
      getch();
      break;
    }
  }
  va_end(ap);
}
int main(int argc, char **argv)
{
  char f[100];
  char z[100];
  minscanf("%s , %s", f, z);
  printf("%s %s\n", f, z);
}

#define MAXSTACK 5000
int stack[MAXSTACK];
int *stackp = stack;
int getch(void)
{
  return (stackp != stack) ? *--stackp : getchar();
}

void ungetch(int c)
{
  if ((stackp - stack) >= MAXSTACK - 1) {
    printf("error: stack full\n");
    return;
  }
  *stackp++ = c;
}
