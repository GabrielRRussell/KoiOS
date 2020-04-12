#ifndef SERIAL_H
#define SERIAL_H

enum COM_PORTS {
  COM1 = 0x3F8,
  COM2 = 0x2F8,
  COM3 = 0x3E8,
  COM4 = 0x2E8
};

void serial_init(uint16_t port);

uint8_t receive_ready(uint16_t port);
uint8_t transmit_ready(uint16_t port);

uint8_t read_serial(uint16_t port);
void write_serial(uint16_t port, uint8_t data);

#endif
