#include <stdio.h>
#define MAX_SIZE 1000
int readline(char line[], int lim);
int remove_comments(char from[], char to[], int comment_star);
int only_blanks(char arr[]);

int main() {
  char line[MAX_SIZE];
  char to[MAX_SIZE];
  int size;
  int comment_star = 0;
  while ((size = readline(line, MAX_SIZE)) > 0) {
    comment_star = remove_comments(line, to, comment_star);
    printf("%s", to);
  }
}

int only_blanks(char arr[]) {
  int i;
  for (i = 0; arr[i] != '\0'; ++i) {
    if (arr[i] != ' ' && arr[i] != '\t' && arr[i] != '\n') {
      return 0;
    }
  }
  return 1;
}

int remove_comments(char from[], char to[], int comment_star) {
  int in_string = 0;
  int i;
  int k;
  int check_for_blanks = comment_star;
  for (k = 0, i = 0; from[i] != '\0'; ++i) {
    if (in_string) {
      to[k] = from[i];
      ++k;
      if (from[i] == '\"') {
        in_string = 0;
      }
    } else if (comment_star) {
      if (from[i] == '*' && from[i + 1] == '/') {
        comment_star = 0;
        check_for_blanks = 1;
        ++i;
      }
    } else if (from[i] == '/' && from[i + 1] == '/') {
      check_for_blanks = 1;
      to[k] = '\0';
      break;
    } else if (from[i] == '/' && from[i + 1] == '*') {
      check_for_blanks = 1;
      comment_star = 1;
    } else {
      if (from[i] != ' ' && from[i] != '\n' && from[i] != '\t') {
        check_for_blanks = 0;
      }
      if (from[i] == '\"') {
        in_string = 1;
      }
      to[k] = from[i];
      ++k;
    }
  }
  if (check_for_blanks) {
    to[k] = '\0';
  }
  if (check_for_blanks && only_blanks(to)) {
    to[0] = '\0';
  } else {
    to[k] = '\0';
  }
  return comment_star;
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
