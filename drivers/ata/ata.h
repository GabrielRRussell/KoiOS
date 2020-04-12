#ifndef ATA_H
#define ATA_H

// http://lateblt.tripod.com/atapi.htm
enum IDE_REGISTERS {
  DATA_REGISTER = 0x1F0,
  ERROR_REGISTER = 0x1F1,
  FEATURES_REGISTER = 0x1F1,
  SECTOR_COUNT_REGISTER = 0x1F2,
  LBA_LO_REGISTER = 0x1F3,
  LBA_MI_REGISTER = 0x1F4,
  LBA_HI_REGISTER = 0x1F5,
  DRIVE_HEAD_REGISTER = 0x1F6,
  STATUS_REGISTER = 0x1F7,
  COMMAND_REGISTER = 0x1F7,
  ALTERNATE_STATUS_REGISTER = 0x3F6,
  DEVICE_CONTROL_REGISTER = 0x3F6
};

enum STATUS_REGISTER_MASKS {
  ERROR_MASK = 1,
  INDEX_MARK_MASK = 2,
  DATA_CORRECTED_MASK = 4,
  DATA_TRANSFER_REQUESTED_MASK = 8,
  SEEK_COMPLETE_MASK = 16,
  DEVICE_FAULT_MASK = 32,
  DEVICE_READY_MASK = 64,
  BUSY_MASK = 128
};

enum ERROR_REGISTER_MASKS {
  ADDRESS_MARK_NOT_FOUND_MASK = 1,
  TRACK_ZERO_NOT_FOUND_MASK = 2,
  COMMAND_ABORTED_MASK = 4,
  MEDIA_CHANGE_REQUESTED = 8,
  ID_MARK_NOT_FOUND_MASK = 16,
  MEDIA_CHANGED_MASK = 32,
  UNCORRECTABLE_DATA_ERROR = 64,
  BAD_BLOCK_ERROR = 128
};

// https://wiki.osdev.org/ATA_Command_Matrix
enum ATA_COMMANDS {
  READ_SECTORS_WITH_RETRY = 0x20
};

#endif
