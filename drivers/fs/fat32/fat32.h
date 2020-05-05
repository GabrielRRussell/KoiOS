#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

typedef struct BPB_t {
  uint8_t  BPB_JUMP_OP[3];
  uint8_t  BPB_OEM_IDENTIFIER[8];
  uint16_t BPB_BYTES_PER_SECTOR;
  uint8_t  BPB_SECTORS_PER_CLUSTER;
  uint16_t BPB_RESERVED_SECTORS;
  uint8_t  BPB_NUMBER_OF_FATS;
  uint16_t BPB_NUMBER_OF_DIRECTORY_ENTRIES;
  uint16_t BPB_TOTAL_SECTORS;
  uint8_t  BPB_MEDIA_DESCRIPTOR;
  uint16_t BPB_SECTORS_PER_FAT_UNUSED;
  uint16_t BPB_SECTORS_PER_TRACK;
  uint16_t BPB_NUMBER_OF_HEADS;
  uint32_t BPB_HIDDEN_SECTORS;
  uint32_t BPB_LARGE_TOTAL_SECTORS;

  uint32_t EBPB_SECTORS_PER_FAT;
  uint16_t EBPB_FLAGS;
  uint16_t EBPB_FAT_VERSION;
  uint32_t EBPB_ROOT_CLUSTER_START;
  uint16_t EBPB_FSINFO_SECTOR;
  uint16_t EBPB_BACKUP_SECTOR;
  uint8_t  EBPB_RESERVED[12];
  uint8_t  EBPB_DRIVE_NUMBER;
  uint8_t  EBPB_NT_FLAGS;
  uint8_t  EBPB_SIGNATURE;
  uint32_t EBPB_SERIAL_NUMBER;
  uint8_t  EBPB_VOLUME_LABEL[11];
  uint8_t  EBPB_SYSTEM_IDENTIFIER[8];
}  __attribute__((packed)) BPB_t;

typedef struct DirectoryEntry_t {
	char name[8];
	char ext[3];
	uint8_t attrib;
	uint8_t userattrib;

	char undelete;
	uint16_t createtime;
	uint16_t createdate;
	uint16_t accessdate;
	uint16_t clusterhigh;
  uint16_t modifiedtime;
	uint16_t modifieddate;
	uint16_t clusterlow;
	uint32_t filesize;

} __attribute__ ((packed)) DirectoryEntry_t;

typedef struct FAT32_attribute_t {
  uint8_t readOnly : 1;
  uint8_t hidden   : 1;
  uint8_t system   : 1;
  uint8_t volume_id: 1;
  uint8_t directory: 1;
  uint8_t archive  : 1;
  uint8_t unused   : 2;
} __attribute__ ((packed)) FAT32_attribute_t;

enum ENTRY_TYPES {
  NO_MORE_ENTRIES_IN_DIRECTORY  = 0,
  ENTRY_UNUSED                  = 1,
  LONG_FILE_NAME                = 2,
  ERROR                         = 0xFF
};

uint32_t find_file_entry(char name[8], char ext[3], uint32_t bootSector);

#endif
