#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINESIZE 80
char* readline(int lim);
int main(void)
{
  char* c;
  while ((c = readline(80)) != NULL) {
    while (*c) {
      /* nonvisible ascii characters live in 0-32 and 127 (DEL) */
      if (*c > 32 && *c != 127) {
        printf("%c", *c);
      } else {
        printf("(0x%x)", *c);
      }
      ++c;
    }
    printf("\n");
  }
}

char* readline(int lim)
{
  char tmp[lim];
  int c, i;
  i = 0;
  while ((c = getchar()) != EOF) {
    tmp[i++] = c;
    if (c == '\n') {
      break;
    }
    if (i >= lim - 2) { /* -1 for \n, -1 for \0 */
      /* split line by inserting nl */
      tmp[i++] = '\n';
      break;
    }
  }
  if (!i) {
    return NULL;
  }
  tmp[i] = '\0';
  return strdup(tmp);
}
