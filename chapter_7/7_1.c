#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* extract the program name from a unix path */
char* getbasename(char* s)
{
  char* s2;
  for (s2 = s + strlen(s); s2 != s && *s2 != '/'; --s2);
  if (*s2 == '/')
    return s2 + 1;
  else
    return s;
}

int main(int argc, char** argv)
{
  int c;
  char* basename = getbasename(argv[0]);
  int lower = !strcmp(basename, "lower");
  printf("%s\n", basename);

  while ((c = getchar()) != EOF) {
    if (lower) 
      c = tolower(c);
    else
      c = toupper(c);
    putchar(c);
  }
  return 0;
}
