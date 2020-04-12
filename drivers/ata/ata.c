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

void ata_send_command(uint16_t command) {
  /*
    Wait til the device is ready, disable interrupts,
    then issue the command, restore interrupts
  */
  ata_busy_poll();
  asm volatile("cli");
  ata_device_ready_poll();
  outw(COMMAND_REGISTER, command);
  asm volatile("sti");
}

void ata_read_sector(uint32_t lba, uint8_t sectors, unsigned char *buf) {
  outw(DRIVE_HEAD_REGISTER, (uint16_t) (lba >> 24 | 244) );
  outb(SECTOR_COUNT_REGISTER, sectors);
  outb(LBA_LO_REGISTER, (uint8_t) lba & 0x000000FF);
  outb(LBA_MI_REGISTER, (uint8_t) (lba & 0x0000FF00 >> 8));
  outb(LBA_HI_REGISTER, (uint8_t) (lba & 0x00FF0000 >> 16));
  ata_send_command(READ_SECTORS_WITH_RETRY);

  while (inb(STATUS_REGISTER) & DATA_TRANSFER_REQUESTED_MASK == 8);
  for (int i = 0; i < sectors * 512; i++) {
    buf[i] = inb(DATA_REGISTER);
  }
}
