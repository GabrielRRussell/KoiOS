#include <stdint.h>
#include "serial.h"

void serial_init(uint16_t port) {
  outb(port + 1, 0x00);
  outb(port + 3, 0x80);
  outb(port + 0, 0x03);
  outb(port + 1, 0x00);
  outb(port + 3, 0x03);
  outb(port + 2, 0xC7);
  outb(port + 4, 0x0B);
}

uint8_t receive_ready(uint16_t port) {
  return inb(port + 5) & 1;
}

uint8_t transmit_ready(uint16_t port) {
  return inb(port + 5) & 0x20);
}

uint8_t read_serial(uint16_t port) {
  while (receive_ready() == 0);
  return inb(port);
}

void write_serial(uint16_t port, uint8_t data) {
  while (transmit_ready() == 0);
  outb(port, data);
}
