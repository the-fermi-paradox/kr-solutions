// Exercise 1_24
// Rudimentary Syntax Checker
// Write a program to check a C program for rudimentary syntax
// errors like unbalanced parentheses, brackets and braces.
// Don't forget about quotes, both single and double, escape
// sequences and comments. (This program is hard if you do it
// in full generality.)
#include <stdio.h>

#define MAX_SIZE 1000
#define NONE 0
#define STRING 1
#define ESCAPE 2
#define CHARCODE 4
#define STRESC 3
#define CHARESC 6
#define HEXESC 8
#define CHAR_HEX_ESC 14
#define COMMENT 16
#define SLASH_COMMENT 48
#define STAR_COMMENT 80
#define OCTESC 128
#define ERROR 256
#define DIGIT_CAP 3
int readline(char line[], int lim);
int stacksize = 0;
int loop(char from[], char stack[], int line_count, int state);

int main()
{
  char line[MAX_SIZE];
  char stack[MAX_SIZE];
  int line_count = 1;
  int state = NONE;
  while ((readline(line, MAX_SIZE)) > 0) {
    state = loop(line, stack, line_count, state);
    if (state & ERROR) {
      return 1;
    }
    ++line_count;
  }
  if (stack[0] != '\0') {
    int i = 0;
    while (stack[i] != '\0') {
      printf("mismatched %c", stack[i]);
      ++i;
    }
    return 1;
  }
  return 0;
}

char pop(char stack[]) {
  if (!stacksize) {
    return '\0';
  }
  char ret = stack[stacksize - 1];
  stack[stacksize - 1] = '\0';
  --stacksize;
  return ret;
}

int push(char stack[], char topush) {
  stack[stacksize] = topush;
  return ++stacksize;
}

char match(char val) {
  switch (val) {
    case '{':
      return '}';
    case '}':
      return '{';
    case '(':
      return ')';
    case ')':
      return '(';
    case '[':
      return ']';
    case ']':
      return '[';
    case '\'':
      return '\'';
    case '\"':
      return '\"';
  }
  return '\0';
}

int loop(char from[], char stack[], int line_count, int state)
{
  int i;
  int charcount = 0;
  int hex_count = 0;
  int oct_count = 0;
  for (i = 0; from[i] != '\0' && from[i] != '\n'; ++i) {
    if (state & ERROR) {
      return ERROR;
    }
    else if (state == NONE) {
      if (from[i] == '\"') {
        state |= STRING;
      } else if (from[i] == '\'') {
        charcount = 0;
        state |= CHARCODE;
      } else if (from[i] == '\\') {
        state |= ERROR;
        printf("%d: stray '\\' in program", line_count);
      } else if (from[i] == '/' && from[i + 1] == '/') {
        state |= SLASH_COMMENT;
      } else if (from[i] == '/' && from[i + 1] == '*') {
        state |= STAR_COMMENT;
      } else if (from[i] == '{' || from[i] == '(' || from[i] == '[') {
        push(stack, from[i]);
      } else if (from[i] == '}' || from[i] == ')' || from[i] == ']') {
        char popped = pop(stack);
        if (popped != match(from[i])) {
          state |= ERROR;
          printf("match: %c\n", match(from[i]));
          printf("%d: mismatched %c to %c", line_count, from[i], popped);
        }
      }
    }
    else if (state & STAR_COMMENT) {
      if (from[i] == '*' && from[i + 1] == '/') {
        state ^= STAR_COMMENT;
      }
    }
    else if (state & OCTESC) {
      if ((from[i] == '\'' && (state & CHARCODE)) || (from[i] == '"' && (state & STRING))) {
        state &= NONE;
      } else if (oct_count > DIGIT_CAP) {
        if (state & CHARCODE) {
          state |= ERROR;
          printf("%d: multicharacter character constant", line_count);
        } else {
          state ^= ESCAPE;
          state ^= OCTESC;
        }
      } else {
        ++oct_count;
      }
    }
    else if (state & HEXESC) {
      if ((from[i] == '\'' && (state & CHARCODE)) || (from[i] == '"' && (state & STRING))) {
        state &= (hex_count 
            ? NONE 
            : printf("%d: \\x used with no following hex digits", line_count), ERROR);
      } else if (!(from[i] >= '0' && from[i] <= '9') 
            && !(from[i] >= 'A' && from[i] <= 'F') 
            && !(from[i] >= 'a' && from[i] <= 'f')) {
        state ^= HEXESC;
        state ^= ESCAPE;
        if (state & CHARCODE) {
          state |= ERROR;
          printf("%d: multicharacter character constant", line_count);
        }
      } else {
        ++hex_count;
      }
    }
    else if (state & ESCAPE) {
      // These are all the valid escape sequences in C
      if (from[i] != 'a' && from[i] != 'b' &&
          from[i] != 'f' && from[i] != 'n' &&
          from[i] != 'r' && from[i] != 't' &&
          from[i] != 'v' && from[i] != '\\' &&
          from[i] != '?' && from[i] != '\'' &&
          from[i] != '"' && from[i] != 'x' &&
          (from[i] < '0' || from[i] > '7')) {
        state |= ERROR;
        printf("%d: unrecognized escape sequence", line_count);
      } else if (from[i] == 'x') {
        state |= HEXESC;
        hex_count = 0;
      } else if (from[i] >= '0' && from[i] <= '7') {
        state |= OCTESC;
        oct_count = 1;
      } else {
        state ^= ESCAPE;
      }
    }
    else if (state & STRING) {
      if (from[i] == '\\' && !(state & ESCAPE)) {
        state |= ESCAPE;
      } else if (from[i] == '"'){
        state ^= STRING;
      }
    }
    else if (state & CHARCODE) {
      if (from[i] == '\'') {
        state ^= CHARCODE;
      } else if (charcount > 1) {
        state |= ERROR;
        printf("%d: multicharacter character constant", line_count);
      } else if (from[i] == '\\') {
        ++charcount;
        state |= ESCAPE;
      } else {
        ++charcount;
      }
    }
  }
  if (from[i] == '\n') {
    if (state & STRING) {
      state |= ERROR;
      printf("%d: unterminated string", line_count);
    }
    else if (state & CHARCODE) {
      state |= ERROR;
      printf("%d: unterminated character constant", line_count);
    }
    else if (!(state & STAR_COMMENT)) {
      state &= NONE;
    }
  }
  return state;
}

int readline(char line[], int lim)
{
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
