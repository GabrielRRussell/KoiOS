#include "screen.h"
#include "../../cpu/ports.h"

int getByteOffset(uint8_t x, uint8_t y);


void kput_char(char c, uint8_t x, uint8_t y, uint8_t attr) {
  int offset = getByteOffset(x, y);
  unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY;

  vidmem[offset]   = c;
  vidmem[offset+1] = attr;
}

void kclear_screen(uint8_t attr) {
  int maximum = 25 * 80;
  unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY;

  for (int i = 0; i < maximum; i++) {
      vidmem[i*2]   = ' ';
      vidmem[i*2+1] = attr;
  }
}

/*
  Private Functions and Declarations
*/

int getByteOffset(uint8_t x, uint8_t y) {
  return (x + (y * VGA_WIDTH) * 2);
}
