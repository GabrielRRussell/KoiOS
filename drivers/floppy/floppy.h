#ifndef FLOPPY_H
#define FLOPPY_H

enum FloppyRegisters {
  STATUS_REGISTER_A               = 0x3F0, // R/only
  STATUS_REGISTER_B               = 0x3F1, // R/only
  DIGITAL_OUTPUT_REGISTER         = 0x3F2,
  TAPE_DRIVE_REGISTER             = 0x3F3,
  MAIN_STATUS_REGISTER            = 0x3F4, // R/only
  DATARATE_SELECT_REGISTER        = 0x3F4, // W/only
  DATA_FIFO                       = 0x3F5,
  DIGITAL_INPUT_REGISTER          = 0x3F7,
  CONFIGURATION_CONTROL_REGISTER  = 0x3F7
};

enum DOR_MASKS {
  MASK_MOTD  = 0x80,
  MASK_MOTC  = 0x40,
  MASK_MOTB  = 0x20,
  MASK_MOTA  = 0x10,
  MASK_IRQ   = 0x08,
  MASK_RESET = 0x04,
  MASK_DSEL1 = 0x03
};

enum MSR_MASKS {
  MASK_RQM  = 0x80,
  MASK_DIO  = 0x40,
  MASK_NDMA = 0x20,
  MASK_CB   = 0x10,
  MASK_ACTD = 0x08,
  MASK_ACTC = 0x04,
  MASK_ACTB = 0x02,
  MASK_ACTA = 0x01
};

enum CCR_DSR_MASKS {
  MASK_LOSPEED = 0,
  MASK_HISPEED = 3
};

#endif
