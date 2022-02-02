#include <stdio.h>

int main() {
  int chars = 0;
  int nls = 0;
  int words = 0;
  int c;
  int inword = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      ++nls;
    }
    // If we aren't already in a word and we find a character
    // we're now in a word; this transition is what we use to track words
    if (c == '\n' || c == ' ' || c == '\t') {
      inword = 0;
      // If we're in a word and we find a special character, 
      // we're no longer in a word
    } else if (!inword) {
      inword = 1;
      ++words;
    }
    ++chars;
  }
  printf("words: %d, lines: %d, chars: %d", words, nls, chars);
}
