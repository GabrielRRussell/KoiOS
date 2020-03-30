#include "ports.h"

uint8_t inb(uint8_t port) {
  uint8_t in;
  asm volatile("in %%dx, %%al" : "=a" (in) : "d" (port));
  return in;
}

uint8_t outb(uint8_t port, uint8_t byte) {
  asm volatile("out %%al, %%dx" : : "a" (byte), "d" (port));
}
