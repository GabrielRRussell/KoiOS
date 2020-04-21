#include "isr.h"
#include "../ports.h"

void idt_init(void) {
  // Our Assembly Functions
  extern int load_idt();
  extern int isr_stub();

  // Remap the PIC
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 40);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  // Install isr_stub to all 256 IDT Entries
  for (int i = 0; i < 257; i++) {
    install_isr((unsigned long) isr_stub, i);
  }


  // Create the pointer to our IDT
  unsigned long idt_ptr[2];
  unsigned long idt_address = (unsigned long) IDT;
  idt_ptr[0] = (sizeof (struct idt_entry) * 256) + ((idt_address & 0xFFFF) << 16);
  idt_ptr[1] = idt_address >> 16;
  // Install the IDT
  load_idt(idt_ptr);
}

// Install a generic function, by default we use the isr_stub()
void install_isr(unsigned long funct, uint8_t isr) {
  IDT[isr].caller_low = funct & 0xFFFF;
  IDT[isr].caller_high = (funct & 0xFFFF0000) >> 16;
  IDT[isr].segment = 0x8;
  IDT[isr].null = 0;
  IDT[isr].attr = 0x8E;
}
