#include "fat32.h"

#include "../../ata/ata.h"
#include "../../screen/screen.h"
#include "../../serial/serial.h"

#include "../../../libk/string/string.h"

#include "../../../kernel/memory/memory.h"

uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster, uint32_t first_data_sector);
uint8_t  parse_entry(DirectoryEntry_t *entry);

// Returns the Disk Address of the File Entry when found
uint32_t find_file_entry(char name[8], char ext[3], uint32_t bootSector) {
  // Get all of our BPB Info Necessary to find the first sectors
  BPB_t *bpb = kmalloc(512);
  ata_read_sector(bootSector, 1, bpb);

  uint32_t reserved_sectors = bpb->BPB_RESERVED_SECTORS;
  uint32_t fat_size = bpb->EBPB_SECTORS_PER_FAT * bpb->BPB_NUMBER_OF_FATS;
  uint32_t first_data_sector = reserved_sectors + fat_size;

  // Now we know where our first cluster is, so we allocate a block for it
  DirectoryEntry_t *entryBuffer = kmalloc(512);
  ata_read_sector(first_data_sector, 1, entryBuffer);

  // Iterate through each and every sector in the FAT. We'll only read the first
  for (uint32_t i = 0; i < fat_size / 2; i++) {
      // Iterate through 16 entries, SectorSize / 32byte entries
      for (int i = 0; i < 512 / 32; i++) {
        // Compare the Strings
        uint8_t a = cmpStr(name, entryBuffer[i].name, 8);
        uint8_t b = cmpStr(ext, entryBuffer[i].ext, 3);
        // If they match, return the disk address of the entry
        if (a && b) { return (first_data_sector * 512) + (i * 32); }
      }
  }
  // Return an invalid address if we can't find it.
  return 0xFFFFFFFF;

}

uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster, uint32_t first_data_sector) {
  return ((cluster - 2) * sectors_per_cluster) + first_data_sector;
}

// Determine if the entry is Unused, Long_File, or Regular, or if Dir is Empty
uint8_t parse_entry(DirectoryEntry_t *entry) {
  if ((unsigned char) entry->name[0] == 0) {
    return NO_MORE_ENTRIES_IN_DIRECTORY;
  } else if ((unsigned char) entry->name[0] == 0xE5) {
    return ENTRY_UNUSED;
  }

  if (entry->attrib == 0x0F) {
    return LONG_FILE_NAME;
  }

  return REGULAR_FILE;
}
