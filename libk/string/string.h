#ifndef STRING_H
#define STRING_H

uint8_t cmpStr(char *src1, char *src2, uint32_t bytes);
int strlen(char *str);

void reverseStr(char str[]);

char int_to_char(int num);
void intToStr(char str[], unsigned int n, uint8_t base);

void strCat(char str1[], char str2[]);

#endif
