#include <stdio.h>
#include <ctype.h>
int htoi(char hex[]);
int chtoi(char hex);
int main() {
  printf("%d", htoi("0x1000000\0"));
}

int htoi(char hex[]) {
  int i = 0;
  int n = 0;

  /* Check for optional starting '0x' */
  if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
    i = 2; 
  }
  /* Loop through the string */
  while (hex[i] != '\0' && hex[i] != '\n') {
    /* On failure to parse just return 0 */
    if ((hex[i] < '0' || hex[i] > '9') && (hex[i] < 'A' || hex[i] > 'F') && (hex[i] < 'a' || hex[i] > 'f')) {
      return 0;
    }
    /* Each 'place' multiply by 16 */
    n = n * 16 + chtoi(hex[i]);
    ++i;
  }
  return n;
}

int chtoi(char hex) {
  if (isdigit(hex)) {
    return hex - '0';
  }
  hex = toupper(hex); 
  hex -= 55;
  return hex;
}
