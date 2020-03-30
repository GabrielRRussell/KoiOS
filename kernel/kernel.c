#include <stdint.h>

#include "../cpu/ports.h"
#include "../drivers/screen/screen.h"

void kmain() {
  kclear_screen(WHITE_ON_CYAN);
  kput_char('F', 0, 0, WHITE_ON_CYAN);
}
