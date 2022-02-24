#include <stdio.h>
/*
* Exercise 5-5: Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example,
* strncpy(s, t, n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/
#define SIZE 1000
static char* strnncat(char* s, char* t, int n);
static char* strnncpy(char* s, char* t, int n);
static int strnncmp(char* s, char* t, int n);
int main()
{
  char s[SIZE] = "ACCC";
  char t[SIZE] = "ACCD";
  /*strnncpy(s, t, 1);*/
  printf("exp: %d %d\n", 'C' - 'D', strnncmp(s, t, 4));

  // FALSE
  char y[SIZE] = "AC";
  char z[SIZE] = "ACCC";
  printf("exp: %d %d\n", 0 - 'C', strnncmp(y, z, 4));

  // FALSE
  char a1[SIZE] = "C";
  char a2[SIZE] = "B";
  printf("exp: %d %d\n", 'C' - 'B', strnncmp(a1, a2, 1));

  // TRUE
  char a3[SIZE] = "C";
  char a4[SIZE] = "C";
  printf("exp: 0 %d\n", strnncmp(a3, a4, 1));

  // FALSE
  char a5[SIZE] = "CCC";
  char a6[SIZE] = "CCCD";
  printf("exp: %d %d\n", 0 - 'D', strnncmp(a5, a6, 4));

  // TRUE
  char a7[SIZE] = "CCCD";
  char a8[SIZE] = "CCC";
  printf("exp: 0 %d\n", strnncmp(a7, a8, 3));

  char a9[SIZE] = "ACCZ";
  char a10[SIZE] = "BCC";
  printf("exp: %d %d\n", 'A' - 'B', strnncmp(a9, a10, 3));
}
static char* strnncpy(char* s, char* t, int n)
{
  int c = 0;
  char* og = s;
  for (c = 0; c < n && (*s++ = *t++); ++c);
  while (c++ < n)
    *s++ = '\0';
  return og;
}

static char* strnncat(char* s, char* t, int n)
{
  char* p = t;
  char* og = s;
  /* Get to the end */
  while (*s)
    ++s;
  while (p - t < n && (*s++ = *p++));
  /* Always terminate */
  *s++ = '\0';
  return og;
}

static int strnncmp(char* s, char* t, int n)
{
  int i;
  for (i = 0; i < n - 1 && *s == *t; ++i, ++s, ++t);
  return *s - *t;
}
