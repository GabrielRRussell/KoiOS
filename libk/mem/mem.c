#include <stdint.h>
#include "mem.h"

void memcpy(uint8_t *src, uint8_t *dst, int bytes) {
  for (int i; i < bytes; i++) {
    dst[i] = src[i];
  }
}
