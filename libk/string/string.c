#include <stdint.h>
#include "string.h"

uint8_t cmpStr (char *src1, char *src2, uint32_t bytes) {
  // Iterate through each byte
  for (uint32_t i = 0; i < bytes; i++) {
    // Compare the byte, if not equal, return
    if (src1[i] != src2[i]) {
      return 0;
    }
  }
  // If we exited, that means the strings are equal, bail with True
  return 1;
}

int strlen(char *str) {
  int i = 0;
  while (str[i] != 0) i++;
  return i;
}

void reverseStr(char str[]) {
  int c, i, j;
  for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

char int_to_char(int num) {
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}

// Unsigned Int of base 2-16
void intToStr(char str[], unsigned int n, uint8_t base) {

  int i = 0;

  while (n > 0) {
    str[i++] = int_to_char(n % base);
    n /= base;
  }
  str[i] = 0;

  reverseStr(str);

  return;
}

// DON'T USE WITHOUT ALLOCATING MORE SPACE OR YOU'LL MESS UP CODE
void strCat(char str1[], char str2[]) {
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int i;

  for (i = 0; i < len2; i++) {
    str1[len1 + i] = str2[i];
  }
  str1[len1 + i + 1] = 0;
}
