#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
  va_list ap;
  char spec[500];
  char* specp = spec;
  char *p, *sval;
  void* pval;
  long int ival;
  char islong = 0;
  unsigned long int uval;
  double dval;
  va_start(ap, fmt);

  for(p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    /* Build special string */
    do {
      if (*p == 'l') {
        islong++;
      }
      *specp++ = *p++;
    } while(*p && *p != 'x' && *p != 'd' && *p != 'i' && *p != 'o' && *p != 'c'
        && *p != 'u' && *p != 'f' && *p != 's');
    *specp++ = *p;
    *specp = '\0';
    switch (*p) {
    case 'd': /* Fallthrough */
    case 'i':
      ival = islong ? va_arg(ap, long int) : va_arg(ap, int);
      printf(spec, ival);
      break;
    case 'o':
      ival = islong ? va_arg(ap, long int) : va_arg(ap, int);
      ival = va_arg(ap, int);
      printf(spec, ival);
      break;
    case 'x':
      ival = islong ? va_arg(ap, long int) : va_arg(ap, int);
      ival = va_arg(ap, int);
      printf(spec, ival);
      break;
    case 'u':
      uval = islong ? va_arg(ap, unsigned long int) : va_arg(ap, unsigned int);
      printf(spec, uval);
      break;
    case 'c':
      ival = islong ? va_arg(ap, long int) : va_arg(ap, int);
      printf(spec, ival);
      break;
    case 'p':
      pval = va_arg(ap, void*);
      printf(spec, pval);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf(spec, dval);
      break;
    case 's':
      sval = va_arg(ap, char*);
      printf(spec, sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}
int main(void)
{
  minprintf("%s\n", "hello, world");
  minprintf("%10s\n", "hello, world");
  minprintf("%.10s\n", "hello, world");
  minprintf("%-10s\n", "hello, world");
  minprintf("%.15s\n", "hello, world");
  minprintf("%-15s\n", "hello, world");
  minprintf("%15.10s\n", "hello, world");
  minprintf("%-15.10s\n", "hello, world");
#include <limits.h>
  minprintf("%lu\n", ULONG_MAX);
  minprintf("%u\n", UINT_MAX);
  minprintf("%d\n", INT_MAX);
  minprintf("%ld\n", LONG_MAX);
  minprintf("%ld\n", LONG_MIN);
}
