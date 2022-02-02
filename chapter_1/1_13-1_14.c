// Exercise 1-13
// Histogram
// Write a program to print a histogram of the lengths of words in its input.
// It is easy to draw the histogram with the bars horizontal; a vertical
// orientation is more challenging.
//
// Exercise 1-14
// Histogram Pt. 2
// Write a program to print a histogram of the frequencies of different characters in the output

#include <stdio.h>
#define OUT 0
#define IN  1
#define SIZE 10

int getmax(int arr[], int size);
void printhistogram(int sizes[], int size, int vertical);
void countwords(int sizes[], int max_size);
void countchars(int chars[]);
int shiftcharleft(int val);
int shiftcharright(int val);

int main() {
  int i;
  int sizes[10];
  int chars[shiftcharleft(127)];
  int size = SIZE;
  for (i = 0; i < size; ++i) {
    sizes[i] = 0;
  }
  for (i = 0; i < shiftcharleft(127); ++i) {
    chars[i] = 0;
  }
  // countwords(sizes, size);
  countchars(chars);
  printhistogram(chars, shiftcharleft(127), 0);
}

void countchars(int chars[]) {
  int c;
  while ((c = getchar()) != EOF) {
    if (c >= '!') {
      ++chars[shiftcharleft(c)];
    }
  }
}

int shiftcharleft(int val) {
  return val - '!';
}

int shiftcharright(int val) {
  return val + '!';
}

void countwords(int sizes[], int max_size) {
  int state;
  int wordsize = 0;
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\n' || c == ' ' || c == '\t') {
      if (state == IN) {
        if (wordsize >= max_size) wordsize = max_size - 1;
        sizes[wordsize] += 1;
      }
      state = OUT; 
      wordsize = 0;
    } else if (state == OUT) {
      state = IN;
      wordsize += 1;
    } else {
      ++wordsize;
    }
  }
}

void printhistogram(int sizes[], int size, int vertical) {
  int i;
  int j;
  if (vertical) {
    int max = getmax(sizes, size);
    for (i = max; i > 0; --i) {
      for (j = 0; j < size; ++j) {
        if (sizes[j] == i) {
          putchar(' ');
          putchar('#');
          putchar(' ');
          --sizes[j];
        } else {
          putchar(' ');
          putchar(' ');
          putchar(' ');
        }
      }
      putchar('\n');
    }
    for (i = 0; i < size; ++i) {
      char k = shiftcharright(i);// + '0';
      putchar(' ');
      putchar(k);
      putchar(' ');
    }
  } else {
    for (i = 0; i < size; ++i) {
      char k = shiftcharright(i); // + '0';
      putchar(k);
      putchar(' ');
      putchar('|');
      for (j = 0; j < sizes[i]; ++j) {
        putchar('#');
      }
      putchar('\n');
    }
  }
}

int getmax(int arr[], int size) {
  int max = 0;
  for (int i = 0; i < size; ++i) {
    if (max < arr[i]) {
      max = arr[i];
    }
  }
  return max;
}
