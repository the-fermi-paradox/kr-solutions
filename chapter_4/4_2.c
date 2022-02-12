#include <ctype.h>
#include <stdio.h>
double atof(char s[]);
int main() {
  printf("%f\n", atof("53.2e-1"));
  printf("%f\n", atof("53.2e+0"));
  printf("%f\n", atof("52.1523e2"));
  printf("%f\n", atof("2"));
}
double atof(char s[]) {
  int i, j, sign, scisign;
  double val, pow, sci;
  /* Skip whitespace */
  for (i = 0; s[i] == ' '; ++i); 
  sign = (s[i] == '-') ? -1 : 1; 
  if (s[i] == '-' || s[i] == '+') {
    ++i;
  }
  for (val = 0.0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0'); 
  }
  /* Decimals, obviously */
  if (s[i] == '.') {
    ++i;
  }
  for (pow = 1.0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
    pow *= 10.0;
  }
  /* Scientific notation */
  if (s[i] == 'e' || s[i] == 'E') {
    ++i;
  }
  /* Optional sign */
  scisign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '-' || s[i] == '+') {
    ++i;
  }
  for (sci = 0.0; isdigit(s[i]); ++i) {
    sci = 10.0 * sci + (s[i] - '0'); 
  }
  for (j = 0; j < sci; ++j) {
    /* Since we're dividing by pow, we actually do the opposite of what
     * seems reasonable here */
    if (scisign > 0) {
      pow /= 10.0;
    } else {
      pow *= 10.0;
    }
  }
  return sign * val / pow;
}
