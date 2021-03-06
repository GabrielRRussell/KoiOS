#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_ENCODER_PORT 0x60
#define KEYBOARD_CONTROLLER_PORT 0x64

#define OUTPUT_BUFFER_STATUS_MASK 1
#define INPUT_BUFFER_STATUS_MASK 2
#define SYSTEM_FLAG_MASK 4
#define COMMAND_DATA_MASK 8
#define KEYBOARD_LOCKED_MASK 16
#define AUX_OUTPUT_BUFFER_FULL 32
#define TIMEOUT_MASK 64
#define PARITY_MASK 128

void keyboard_init();

#endif
