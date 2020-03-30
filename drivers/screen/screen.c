#include "screen.h"
#include "../../cpu/ports.h"

// SOFTWARE CURSORS
volatile int x;
volatile int y;

/*
  Private Declarations
*/
int getByteOffset(uint8_t x, uint8_t y);
void set_hardware_cursor(int xPos, int yPos);
void set_software_cursor(int newX, int newY);

/*
  Public Functions
*/

/*
  KERNEL PRINT AT
  STRING = STRING TO PRINT
  XPOS = COLUMN
  YPOS = ROW
  ATTR = ATTRIBUTE BYTE

  Prints string at X/Y, with Attribute Byte placed on each character
*/
void kprint_at(char *string, uint8_t xPos, uint8_t yPos, uint8_t attr) {
  int i;
  set_software_cursor(xPos, yPos);

  while (string[i] != 0) {
    kput_char(string[i], x, y, attr);
  }

  set_hardware_cursor(x, y);
}

/*
  KERNEL PUT CHARACTER
  C = CHARACTER
  XPOS = COLUMN
  YPOS = ROW
  ATTR = ATTRIBUTE BYTE

  Puts Character at X/Y, with Attribute Byte given
*/
void kput_char(char c, uint8_t xPos, uint8_t yPos, uint8_t attr) {
  // Determine Offset from X/Y Given
  int offset = getByteOffset(xPos, yPos);
  unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY;
  // Place c/attr at offset, drawing character
  vidmem[offset]   = (unsigned char) c;
  vidmem[offset+1] = attr;
}

/*
  KERNEL CLEAR SCREEN
  ATTR = ATTRIBUTE BYTE

  Clears Screen with given background color,
  replaces all characters with ' '
*/
void kclear_screen(uint8_t attr) {

  int maximum = VGA_HEIGHT * VGA_WIDTH;
  unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY;

  // Iterate through each possible position at vidmem,
  // replace with ' ' and background color
  for (int i = 0; i < maximum; i++) {
      vidmem[i*2]   = ' ';
      vidmem[i*2+1] = attr;
  }

  set_software_cursor(0, 0);
  set_hardware_cursor(0, 0);

}

/*
  Private Functions
*/

/*
  GET BYTE OFFSET
  Returns a simple formula giving an offset of n bytes,
  from start of Video Memory 0xB8000
*/
int getByteOffset(uint8_t xPos, uint8_t yPos) {
  return (xPos + (yPos * VGA_WIDTH) * 2);
}

/*
  SET HARDWARE CURSOR
  Sets the hardware cursor to the given X/Y position on screen
*/
void set_hardware_cursor(int xPos, int yPos) {
  int offset = yPos * VGA_WIDTH + xPos;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t) (offset & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t) ((offset >> 8) & 0xFF));
}

void set_software_cursor(int newX, int newY) {
  x = newX;
  y = newY;
}
