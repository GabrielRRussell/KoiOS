global load_idt
global isr_stub

extern isr_stub

isr_stub:
  iret

load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti
  ret
