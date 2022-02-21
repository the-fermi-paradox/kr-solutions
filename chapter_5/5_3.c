#include <stdio.h>
#define SIZE 1000
static void strct(char* s, char* t);
int main()
{
  /* Nota bene: s shouldn't be declared like char *s = "Hello", since we're modifying it */
  char s[1000] = "Hello";
  /* It's okay for t though */
  char* t = "World";
  strct(s, t);
  printf("%s", s);
}

static void strct(char* s, char* t)
{
  /* Get to end of s */
  while (*s)
    ++s;
  while ((*s++ = *t++));
}
