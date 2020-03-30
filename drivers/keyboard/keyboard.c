#include "keyboard.h"
#include "../../cpu/types.h"
#include "../ports.h"
#include "../screen.h"
#include "../../cpu/idt.h"

char *current_letter;

const char scancode_ascii[] = {
  '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
  'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D',
  'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?',
  '?', '?', ' '
};

// Private Declarations
static void keyboard_callback();
unsigned char read_keyboard_status();
unsigned char read_keyboard_buffer();
void send_keyboard_controller_command(unsigned char command);
void send_keyboard_encoder_command(unsigned char command);
char translate_scancode(unsigned char scancode);

void keyboard_init() {
  set_handler(33, (u32) keyboard_callback);
}

struct interrupt_frame;
__attribute__((interrupt)) static void keyboard_callback(struct interrupt_frame *frame) {
  unsigned char scancode = read_keyboard_buffer();

  if (scancode >= 0x3A || scancode == 0) {}
  else if (scancode == 0x0E) {}
  else {
     current_letter[0] = translate_scancode(scancode);
     current_letter[1] = 0;
     kprint(current_letter);
  }
  port_byte_out(0x20, 0x20);
}

unsigned char read_keyboard_status() {
  return port_byte_in(0x64);
}

unsigned char read_keyboard_buffer() {
  return port_byte_in(0x60);
}

void send_keyboard_controller_command(unsigned char command) {
  while (1) { if ( (read_keyboard_status() & INPUT_BUFFER_STATUS_MASK) == 0) { break; } }
  port_byte_out(0x64, command);
}

void send_keyboard_encoder_command(unsigned char command) {
  while (1) { if ( (read_keyboard_status() & INPUT_BUFFER_STATUS_MASK) == 0) { break; } }
  port_byte_out(0x60, command);
}

char translate_scancode(unsigned char scancode) {
  return scancode_ascii[scancode];
}
