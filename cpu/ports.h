#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

uint8_t inb(uint8_t port);
void outb(uint8_t port, uint8_t byte);

#endif
