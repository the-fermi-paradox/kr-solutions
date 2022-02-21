#include <stdio.h>
#define SIZE 1000
static int strend(char* s, char* t);
int main()
{
  printf("%d\n", strend("Hellow", "Hello"));
  printf("%d\n", strend("abcdefj", "j"));
  printf("%d\n", strend("abcdefx", "j"));
  printf("%d\n", strend("abcdefx0", "0"));

}
static int strend(char* s, char* t)
{
  char* p = t;
  while (*s) {
    if (*s++ != *p++)
      p = t;
  }
  /* if p reached the end we're good */
  return (*p == '\0');
}
