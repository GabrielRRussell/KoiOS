#include <stdint.h>
#include "memory/manager.h"
#include "../cpu/ports.h"
#include "../cpu/interrupts/isr.h"
#include "../cpu/timer/timer.h"
#include "../drivers/serial/serial.h"
#include "../drivers/screen/screen.h"
#include "../drivers/ata/ata.h"

char *logo0 = "  _  __     _    ____   _____ \n";
char *logo1 = " | |/ /    (_)  / __ \\ / ____|\n";
char *logo2 = " | ' / ___  _  | |  | | (___  \n";
char *logo3 = " |  < / _ \\| | | |  | |\\___ \\ \n";
char *logo4 = " | . \\ (_) | | | |__| |____) |\n";
char *logo5 = " |_|\\_\\___/|_|  \\____/|_____/ \n";
char *logo6 = "                              \n";

uint16_t *dump = (uint16_t*) 0xFFFF;

void gdb_interrupt() {
  kprintf("GDB INTERRUPT");
  return;
}

void kmain(void) {
  kclear_screen(WHITE_ON_CYAN);

  // Init Services
  idt_init();
  serial_init(COM1);
  init_timer(FREQUENCY);
  init_memory_manager();

  /*
  sleep(2);
  kprint_at(logo0, 0, 0, WHITE_ON_CYAN);
  kprint_at(logo1, 0, 1, WHITE_ON_CYAN);
  kprint_at(logo2, 0, 2, WHITE_ON_CYAN);
  kprint_at(logo3, 0, 3, WHITE_ON_CYAN);
  kprint_at(logo4, 0, 4, WHITE_ON_CYAN);
  kprint_at(logo5, 0, 5, WHITE_ON_CYAN);
  kprint_at(logo6, 0, 6, WHITE_ON_CYAN);
  */
  if (inb(STATUS_REGISTER) == 0xFF) {
    kprintf("HALT, FLOATING BUS DETECTED");
    asm volatile("cli");
    asm volatile("hlt");
  }

  write_serial(COM1, '1');

  write_serial(COM1, '2');

  write_serial(COM1, '3');

  write_serial(COM1, '4');

  uintptr_t block1 = malloc();
  uintptr_t block2 = malloc();

  // BLOCK2 == BLOCK3
  free(block2);
  uintptr_t block3 = malloc();

  uintptr_t block4 = malloc();

}
