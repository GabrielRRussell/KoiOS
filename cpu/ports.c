#include "ports.h"

uint8_t inb(int port) {
  uint8_t in;
  asm volatile("in %%dx, %%al" : "=a" (in) : "d" (port));
  return in;
}

void outb(int port, uint8_t byte) {
  asm volatile("out %%al, %%dx" : : "a" (byte), "d" (port));
}
