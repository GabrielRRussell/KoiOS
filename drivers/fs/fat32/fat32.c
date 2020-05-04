#include "fat32.h"

#include "../../ata/ata.h"
#include "../../../kernel/memory/memory.h"

// Give this function the LBA of the bootsector where the BPB is contained
void load_FAT32(uint32_t lba) {

  // Get our 512 bytes ready, then load the sector
  BPB_t *bpb = kmalloc(512);
  ata_read_sector(lba, 1, bpb);

  uint16_t reserved_sectors   = bpb->BPB_RESERVED_SECTORS;
  uint8_t  number_of_fats     = bpb->BPB_NUMBER_OF_FATS;
  uint32_t hidden_sectors     = bpb->BPB_HIDDEN_SECTORS;
  uint32_t total_sectors      = bpb->BPB_LARGE_TOTAL_SECTORS;
  uint32_t fat_size_sectors   = bpb->EBPB_SECTORS_PER_FAT;
  uint32_t first_data_sector  = reserved_sectors +
                               (bpb->NUMBER_OF_FATS * fat_size_sectors);
  uint32_t first_fat_sector   = reserved_sectors;
  uint32_t total_data_sectors = total_sectors - (reserved_sectors + (number_of_fats * fat_size_sectors));
}
