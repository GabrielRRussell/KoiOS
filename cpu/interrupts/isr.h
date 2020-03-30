#ifndef ISR_H
#define ISR_H

/*
  IDT ENTRY FORMAT
  caller_high = First 16 bits of function to be called when fired
  caller_low = Last 16 bits of function to be called when fired
  null = Always 0, so that iret won't throw an exception
  attr = Specific Attribute Selections, won't be needed here
  segment = Memory Addressing Segment, we'll set to 0x8
*/
struct idt_entry {
  unsigned short int caller_low;
  unsigned short int segment;
  unsigned char null;
  unsigned char attr;
  unsigned short int caller_high;
} __attribute__((packed));

// There needs to be 256 IDT Entries, or else it'll fail
struct idt_entry IDT[256];

void install_isr (unsigned long funct, uint8_t isr);
void idt_init(void);

#endif
