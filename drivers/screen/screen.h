#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define VIDEO_MEMORY 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BLINK_MASK 128

enum VGA_COLORS {
  VGA_BLACK = 0,
  VGA_WHITE = 15,
  VGA_BLUE = 1,
  VGA_GREEN = 2,
  VGA_CYAN = 3,
  VGA_RED = 4,
  VGA_MAGENTA = 5,
  VGA_BROWN = 6,
  VGA_GRAY = 7,
  VGA_DARK_GRAY = 8,
  VGA_LIGHT_BLUE = 9,
  VGA_LIGHT_GREEN = 10,
  VGA_LIGHT_CYAN = 11,
  VGA_LIGHT_RED = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_YELLOW = 14
};

enum VGA_ATTRIBUTES {
  WHITE_ON_BLACK = 0x0F,
  BLACK_ON_WHITE = 0xF0,
  RED_ON_WHITE   = 0xF4,
  WHITE_ON_CYAN  = 0x3F
};

void kprintf(char *string);
void kprint_at (char *string, uint8_t xPos, uint8_t yPos, uint8_t attr);
void kput_char (char c, uint8_t x, uint8_t y, uint8_t attr);
void kclear_screen();
void kchange_attribute(uint8_t attr);

#endif
