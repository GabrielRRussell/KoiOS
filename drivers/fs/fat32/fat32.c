#include "fat32.h"

#include "../../ata/ata.h"
#include "../../screen/screen.h"
#include "../../serial/serial.h"

#include "../../../libk/string/string.h"

#include "../../../kernel/memory/memory.h"

uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster);
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


  for (uint32_t i = 0; i < fat_size / 2; i++) {
      // Iterate through 16 entries, SectorSize / 32byte entries
      //TODO: FIX THIS
      for (int i = 0; i < 512 / 32; i++) {
        // Compare the Strings
        uint8_t a = cmpStr(name, entryBuffer[i].name, 8);
        uint8_t b = cmpStr(ext, entryBuffer[i].ext, 3);
        // If they match, return the disk address of the entry
        if (a && b) {
          kfree(1024); // Free the memory we used
          return (first_data_sector * 512) + (i * 32);
        }
      }
  }
  // Return an invalid address if we can't find it.
  kfree(1024);
  return 0xFFFFFFFF;

}

// Gets the sector number from a cluster
uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster) {
  return ((cluster - 2) * sectors_per_cluster) + 2050;
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


/*
  yo wtf why does this work
*/
void* load_file_from_cluster (uint32_t entryAddress, uint32_t fat_lba) {

  uint32_t sector = entryAddress / 512; // Sector Number
  uint8_t offset = (entryAddress % 512) / 32; // Entry Number

  DirectoryEntry_t* buffer = kmalloc(512);
  ata_read_sector(sector, 1, buffer);

  // Find out how large the filesize is
  // Allocate Extra Bytes since we're reading raw sectors
  uint32_t bytesToAllocate = buffer[offset].filesize;
  bytesToAllocate += 512 - (bytesToAllocate % 512);

  uint16_t clusterLow = buffer[offset].clusterlow;
  uint16_t clusterHigh = buffer[offset].clusterhigh;
  // Clear Top Four Bits, since Fat32 only uses 28bits for clusters
  uint32_t cluster = (((clusterHigh & 0x0F) << 16) | clusterLow);
  // We can only read 512 bytes at a time

  uint32_t fileSectorOffset = 0;
  uint32_t fileSector = 0;
  uint32_t* FileTable = kmalloc(512 * 8);
  uint8_t* fileBuffer = kmalloc(bytesToAllocate);
  ata_read_sector(fat_lba, 8, FileTable);

  char *intBuf = kmalloc(11);

  do {
    fileSector = get_sector_from_cluster(cluster, 1);
    ata_read_sector(fileSector, 1, fileBuffer + (fileSectorOffset*512));
    cluster = FileTable[cluster];
    fileSectorOffset++;
  } while (cluster < 0x0FFFFFF8);

  return (void*) fileBuffer;

}
