#include <stdint.h>
#include "ata.h"
#include "../../cpu/ports.h"

void ata_busy_poll(void);
void ata_device_ready_poll(void);

void ata_busy_poll(void) {
  while (inb(STATUS_REGISTER) & BUSY_MASK);
  return;
}

void ata_device_ready_poll(void) {
  while (inb(STATUS_REGISTER) & DEVICE_READY_MASK == 0);
  return;
}

void ata_send_command(uint8_t command) {
  
}
