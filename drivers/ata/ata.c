#include <stdint.h>
#include "ata.h"
#include "../../cpu/ports.h"
#include "../serial/serial.h"

void ata_busy_poll(void);
void ata_device_ready_poll(void);

void ata_busy_poll(void) {
  while (inb(STATUS_REGISTER) & BUSY_MASK);
  return;
}

void ata_drq_poll(void) {
  while ((inb(STATUS_REGISTER) & DATA_TRANSFER_REQUESTED_MASK) == 0);
  return;
}

void ata_device_ready_poll(void) {
  while ((inb(STATUS_REGISTER) & DEVICE_READY_MASK) == 0);
  return;
}

void ata_pio_read_loop(uint16_t *buf) {
    uint16_t data;
    for (int i = 0; i < 256; i++) {
      ata_busy_poll();
      ata_drq_poll();
      data = inw(DATA_REGISTER);
      buf[i] = data;
    }

    for (int i = 0; i < 5; i++) inb(ALTERNATE_STATUS_REGISTER);
}

void ata_read_sector(uint32_t lba, uint8_t sectors, void* buf) {
  /*
    This bit is complicated.
    Send to the drive-head-register, 0xE0 for master, then set the last 4 bits
    of the lba. This register shares multiple values, so we do this here
  */
  outb(DRIVE_HEAD_REGISTER, 0xE0 | (0xF0 << 4) | ((lba >> 24) & 0x0F));
  // Send a null byte to error register as in specs
  outb(ERROR_REGISTER, 0x00);
  // Send sectors to Count Register. s=0==256 sectors! Can't read 0 at once
  outb(SECTOR_COUNT_REGISTER, sectors);
  // Eight low bits of LBA
  outb(LBA_LO_REGISTER, (uint8_t) lba);
  // Next eight bits
  outb(LBA_MI_REGISTER, (uint8_t) (lba >> 8));
  // Final eight bits
  outb(LBA_HI_REGISTER, (uint8_t) (lba >> 16));
  // Send our read command
  outb(COMMAND_REGISTER, READ_SECTORS_WITH_RETRY);

  for (int i = 0; i < sectors; i++) {
    ata_pio_read_loop( (uint16_t) (i * 512) + buf);
  }

  return;

}
