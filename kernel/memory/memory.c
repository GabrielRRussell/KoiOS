#include "memory.h"

uint32_t mPtr = 0xA000; // This is where Safe Memory Starts

// Full Kmalloc with all options
void* kmalloc_f(uint32_t bytes, uint8_t align) {
  if (align) {
    mPtr &= 0xFFFFF000;
    mPtr += 0x1000;
  }

  uint32_t tmp = mPtr;
  mPtr += bytes;
  return tmp;

}

void* kmalloc(uint32_t bytes) {
  return kmalloc_f(bytes, 0);
}

void* kmalloc_align(uint32_t bytes) {
  // KB Align
  return kmalloc_f(bytes, 1);
}
