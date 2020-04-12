#include <stdint.h>
#include "../ports.h"
#include "../interrupts/isr.h"
#include "timer.h"

uint32_t tick = 0;

struct interrupt_frame;
__attribute__((interrupt)) void timer_handler(struct interrupt_frame *frame) {
  (void) frame;
  tick++;
  outb(0x20, 0x20);
}

void init_timer(uint32_t clock_rate) {
  install_isr((unsigned long) timer_handler, 32);
  uint32_t div = 1193180 / clock_rate;
  uint8_t low = (uint8_t) (div & 0xFF);
  uint8_t high = (uint8_t) ((div >> 8) & 0xFF);

  outb(0x43, 0x36);
  outb(0x40, low);
  outb(0x40, high);
}

void msleep(uint32_t milliseconds) {
  uint32_t currentTick = tick;
  while (tick != currentTick + milliseconds);
}

void sleep(uint32_t seconds) {
  msleep(seconds * 1000);
}
