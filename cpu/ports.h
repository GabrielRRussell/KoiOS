#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

uint8_t inb(int port);
void outb(int port, uint8_t byte);

uint16_t inw(int port);
void outw(int port, uint16_t word);

#endif
