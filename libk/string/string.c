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

void intToStr(char str[], unsigned int n) {
  // Keep in mind that a 32bit number can only reach 10 characters long
  int remainder = 0;

  // Find the length of our string.
  int len = 0;
  int m = n;
  while (m != 0) {
    m /= 10;
    len++;
  }

  // Iterate through each digit, write it out
  for (int i = 0; i < len; i++) {
      remainder = n % 10;
      n = n / 10;
      str[len - (i + 1)] = remainder + '0';
  }
  // Terminate the string
  str[len] = 0;

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
