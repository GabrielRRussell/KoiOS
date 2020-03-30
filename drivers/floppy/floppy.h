#ifndef FLOPPY_H
#define FLOPPY_H

#define SECTORS_PER_TRACK 18
#define TRACKS_PER_SIDE 80
#define HEADS_PER_DISK

enum FloppyRegisters {
  STATUS_REGISTER_A              = 0x3F0,
  STATUS_REGISTER_B              = 0x3F1,
  DIGITAL_OUTPUT_REGISTER        = 0x3F2,
  TAPE_DRIVE_REGISTER            = 0x3F3,
  MAIN_STATUS_REGISTER           = 0x3F4, // R/only
  DATARATE_SELECT_REGISTER       = 0x3F4, // W/only
  DATA_FIFO                      = 0x3F5,
  DIGITAL_INPUT_REGISTER         = 0x3F7, // R/only
  CONFIGURATION_CONTROL_REGISTER = 0x3F7 // W/only
};

enum FloppyMasks {
  MASK_DRIVE_0      = 0,
  MASK_DRIVE_1      = 1,
  MASK_DRIVE_2      = 2,
  MASK_DRIVE_3      = 3,
  MASK_DRIVE_RESET  = 4,
  MASK_DMA          = 8,
  MASK_0_MOTOR      = 16,
  MASK_1_MOTOR      = 32,
  MASK_2_MOTOR      = 64,
  MASK_3_MOTOR      = 128
};

void lba_chs(unsigned long lba, unsigned int* cyl, unsigned int* head, unsigned int* sector);

#endif
