#ifndef STRING_H
#define STRING_H

uint8_t cmpStr(char *src1, char *src2, uint32_t bytes);
int strlen(char *str);

void reverseStr(char str[]);
void intToStr(char str[], unsigned int n);

void strCat(char str1[], char str2[]);

#endif
