#include <stdint.h>
#include "../../cpu/interrupts/isr.h"
#include "../../cpu/timer/timer.h"
#include "floppy.h"

int floppy_irq_fired = 0;

/*
1 Turn on the drive's motor and select the drive, using an "outb" command to the DOR IO port.
2 Wait for awhile for the motor to get up to speed, using some waiting scheme.
3 Issue your command byte plus some parameter bytes (the "command phase") to the FIFO IO port.
4 Exchange data with the drive / "seek" the drive heads (the "execution phase"), on the FIFO IO port.
5 Get an IRQ6 at the end of the execution phase, but only if the command HAS an execution phase.
6 Read any "result bytes" produced by the command (the "result phase"), on the FIFO IO port.
7 The commands "Recalibrate", "Seek", and "Seek Relative" do not have a result phase, and require an additional "Sense Interrupt" command to be sent.
*/

void floppy_install(void) {
  install_isr((unsigned long) floppy_handler, 38);

  send_dor_command(MASK_RESET);
  sleep(1);

  send_dor_command(MASK_MOTA);
  sleep(3);


}

struct interrupt_frame;
__attribute__((interrupt)) void floppy_handler(struct interrupt_frame *frame) {
  floppy_irq_fired = 1;
  outb(0x20, 0x20);
}

void send_dor_command(uint8_t mask) {
  outb(DIGITAL_OUTPUT_REGISTER, mask);
}

void wait_floppy_irq() {
  while (floppy_irq_fired != 1);
}
