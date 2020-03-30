#ifndef MEM_H
#define MEM_H

void memcpy(char *src, char *dst, int bytes) {
  for (int i; i < bytes; i++) {
    dst[i] = src[i];
  }
}

#endif
