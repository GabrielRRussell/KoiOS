#include <stdint.h>

#include "../cpu/ports.h"
#include "../cpu/interrupts/isr.h"
#include "../cpu/timer/timer.h"
#include "../drivers/screen/screen.h"
#include "../drivers/ata/ata.h"

char *logo0 = "  _  __     _    ____   _____ \n";
char *logo1 = " | |/ /    (_)  / __ \\ / ____|\n";
char *logo2 = " | ' / ___  _  | |  | | (___  \n";
char *logo3 = " |  < / _ \\| | | |  | |\\___ \\ \n";
char *logo4 = " | . \\ (_) | | | |__| |____) |\n";
char *logo5 = " |_|\\_\\___/|_|  \\____/|_____/ \n";
char *logo6 = "                              \n";

uchar *dump = (char*) 0x10000;

void kmain(void) {
  kclear_screen(WHITE_ON_CYAN);
  idt_init();
  init_timer(FREQUENCY);

  sleep(2);
  kprint_at(logo0, 0, 0, WHITE_ON_CYAN);
  kprint_at(logo1, 0, 1, WHITE_ON_CYAN);
  kprint_at(logo2, 0, 2, WHITE_ON_CYAN);
  kprint_at(logo3, 0, 3, WHITE_ON_CYAN);
  kprint_at(logo4, 0, 4, WHITE_ON_CYAN);
  kprint_at(logo5, 0, 5, WHITE_ON_CYAN);
  kprint_at(logo6, 0, 6, WHITE_ON_CYAN);

  ata_read_sector(0, 1, dump);
  kprintf(dump);

}
