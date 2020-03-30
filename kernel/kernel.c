#include <stdint.h>

#include "../cpu/ports.h"
#include "../drivers/screen/screen.h"

char *logo0 = "  _  __     _    ____   _____ \n";
char *logo1 = " | |/ /    (_)  / __ \\ / ____|\n";
char *logo2 = " | ' / ___  _  | |  | | (___  \n";
char *logo3 = " |  < / _ \\| | | |  | |\\___ \\ \n";
char *logo4 = " | . \\ (_) | | | |__| |____) |\n";
char *logo5 = " |_|\\_\\___/|_|  \\____/|_____/ \n";
char *logo6 = "                              \n";
char *logo7 = "                              ";

void kmain(void) {
  kclear_screen(WHITE_ON_CYAN);
  kprint_at(logo0, 0, 0, WHITE_ON_CYAN);
  kprint_at(logo1, 0, 1, WHITE_ON_CYAN);
  kprint_at(logo2, 0, 2, WHITE_ON_CYAN);
  kprint_at(logo3, 0, 3, WHITE_ON_CYAN);
  kprint_at(logo4, 0, 4, WHITE_ON_CYAN);
  kprint_at(logo5, 0, 5, WHITE_ON_CYAN);
  kprint_at(logo6, 0, 6, WHITE_ON_CYAN);
  kprint_at(logo7, 0, 7, WHITE_ON_CYAN);
}
