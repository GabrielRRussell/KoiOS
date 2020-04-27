#ifndef STRING_H
#define STRING_H

uint8_t cmpStr(char *src1, char *src2, uint32_t bytes);
int strLen(char *str);

void reverseStr(char str[]);
void intToStr(char str[], int32_t integer);

#endif
