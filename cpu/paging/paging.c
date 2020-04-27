#include <stdint.h>
#include "../../kernel/kernel.h"
#include "../interrupts/isr.h"
#include "../../libk/string/string.h"

char error_buf[11]; // largest number 32bit uint can display is ten digits

struct interrupt_frame;
__attribute__((interrupt)) void page_fault_handler (struct interrupt_frame *frame, uint32_t error_code) {
  intToStr(error_buf, error_code);
  PANIC(error_buf);
}
