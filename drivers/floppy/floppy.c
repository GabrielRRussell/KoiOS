/*
#include "floppy.h"
#include "../ports.h"
#include "../../cpu/idt.h"
#include "../../cpu/timer.h"

int floppy_irq_fired = 0;

void lba_chs (unsigned long lba, unsigned int* cyl, unsigned int* head, unsigned int* sector) {
  *cyl = (lba / SECTORS_PER_TRACK) / HEADS_PER_DISK);
  *head = (lba / SECTORS_PER_TRACK) % HEADS_PER_DISK);
  *sector = (lba % SECTORS_PER_TRACK) + 1;
}

struct interrupt_frame;

__attribute__((interrupt)) void floppy_irq_callback (struct interrupt_frame *frame) {
  floppy_irq_fired = 1;
  port_byte_out(0x20, 0x20);
}

void floppy_disk_wait() {
  while (floppy_irq_fired == 0);
  floppy_irq_fired = 0;
}

void floppy_init() {
  set_handler(38, (u32) floppy_irq_callback);

  port_byte_out(0x0A, 0x06); // Mask DMA Channel 2
  port_byte_out(0xD8, 0xFF); // Reset Master FF
  port_byte_out(0x04, 0x00); // Address = 0x7E00, Second Byte
  port_byte_out(0x04, 0x7E); // Address First Byte
  port_byte_out(0xD8, 0xFF); // Reset Master FF
  port_byte_out(0x05, 0xFF); // Count to 0x23ff (Number of Bytes in a 3.5 Floppy Disk Track) Second Byte
  port_byte_out(0x05, 0x23); // First Byte
  port_byte_out(0x80, 0x00); // External Page Register = 0
  port_byte_out(0x0A, 0x02); // Unmask DMA Channel 2

}

void floppy_read() {
  port_byte_out(0x0A, 0x06);
  port_byte_out(0x0B, 0x56);
  port_byte_out(0x0A, 0x02);
}

void floppy_write() {
  port_byte_out(0x0A, 0x06);
  port_byte_out(0x0B, 0x5A);
  port_byte_out(0x0A, 0x02);
}

void floppy_write_dor(char val) {
  port_byte_out(DIGITAL_OUTPUT_REGISTER, val);
}
*/
