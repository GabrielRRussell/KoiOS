#include <stdint.h>

#include "../cpu/ports.h"
#include "../cpu/interrupts/isr.h"
#include "../cpu/timer/timer.h"

#include "../drivers/serial/serial.h"
#include "../drivers/screen/screen.h"
#include "../drivers/ata/ata.h"

#include "../libk/string/string.h"

char *logo0 = "  _  __     _    ____   _____ \n";
char *logo1 = " | |/ /    (_)  / __ \\ / ____|\n";
char *logo2 = " | ' / ___  _  | |  | | (___  \n";
char *logo3 = " |  < / _ \\| | | |  | |\\___ \\ \n";
char *logo4 = " | . \\ (_) | | | |__| |____) |\n";
char *logo5 = " |_|\\_\\___/|_|  \\____/|_____/ \n";
char *logo6 = "                              \n";

char *compare1 = "Hello World!";
char *compare2 = "Hello World!";
char *compare3 = "Hello Wurld!";

void kmain(void) {
  kclear_screen(WHITE_ON_CYAN);

  // Init Services
  idt_init();
  serial_init(COM1);
  init_timer(FREQUENCY);

  // All strings are the same length anyways
  uint32_t cmpStrLen = strLen(compare1);

  if (cmpStr(compare1, compare2, cmpStrLen)) {
    kprintf("True");
  } else {
    kprintf("False");
  }

  if (cmpStr(compare1, compare3, cmpStrLen)) {
    kprintf("True");
  } else {
    kprintf("False");
  }

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

}
