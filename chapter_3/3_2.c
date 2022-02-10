#include <stdio.h>
#define MAX_SIZE 1000
int escape(char s[], char t[]);
int unescape(char s[], char t[]);
int readline(char line[], int lim);
int main() {
  char s[MAX_SIZE];
  char t[MAX_SIZE];
  while (readline(t, MAX_SIZE) > 0) {
/*    escape(s, t);
 */   unescape(s, t);
      printf("%s", s);
  }
}

int readline(char line[], int lim) {
  int c;
  int i = 0;
  while ((c = getchar()) != EOF) {
    if (i < lim - 1) {
      line[i] = c;
    }
    ++i;
    if (c == '\n') {
      break;
    }
  }
  if (!i) {
    return 0;
  }
  line[i] = '\0';
  return i;
}

int escape(char s[], char t[]) {
  int i, k, esc;
  i = k = 0;
  while (t[i] != '\0') {
    esc = 0;
    switch(t[i]) {
      case '\t':
        esc = 't';
        break;
      case '\n':
        esc = 'n';
        break;
      case '\b':
        esc = 'b';
        break;
      case ' ':
        esc = 's';
        break;
      default:
        s[k] = t[i];
        ++k;
        ++i;
        break;
    }
    if (esc) {
      s[k] = '\\';
      ++k;
      ++i;
      s[k] = esc;
      ++k;
    }
  }
  s[k] = '\0';
  return 1;
}

int unescape(char s[], char t[]) {
  int i, k, inesc, esc;
  i = k = inesc = 0;
  while (t[i] != '\0') {
    esc = 0;
    /* Map characters to escape sequences */
    if (inesc) {
      switch (t[i]) {
        case 't':
          esc = '\t';
          break;
        case 'n':
          esc = '\n';
          break;
        case 'b':
          esc = '\b';
          break;
        case 's':
          esc = ' ';
          break;
        default:
          esc = 0;
          break;
      }
    } /* Initiate an escape */
    else if (t[i] == '\\') {
      inesc = 1;
      ++i;
      continue;
    }

    if (esc) { /* Handle proper escapes */
      s[k] = esc;
      ++k;
      ++i;
      inesc = 0;
    } else if (inesc) { /* Handle false positive non-escapes */
      s[k] = '\\';
      ++k;
      s[k] = t[i];
      ++k;
      ++i;
      inesc = 0;
    } else { /* Handle every other character */
      s[k] = t[i];
      ++k;
      ++i;
    }
  }
  s[k] = '\0';
  return 1;
}
