#include <stdio.h>
/* getch and ungetch */
#define MAXBUF 100
int bufp;
int buf[MAXBUF]; 

/* For a char array, EOF pushback can be problematic. Why? 
 * char is unique in that its behavior as signed or unsigned is machine-dependant,
 * so EOF's negative value can lie outside of the acceptable range for char.
 * It's signed on my system (GNU/Linux), but I've been using int regardless which handles
 * EOF beautifully.
 *
 * The long and the short of it is that I don't actually need to change anything here. */

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= MAXBUF) {
    printf("error: buf size exceeded\n");
    return;
  }
  buf[bufp++] = c;
}
