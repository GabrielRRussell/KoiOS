#include "fat32.h"

#include "../../ata/ata.h"
#include "../../screen/screen.h"
#include "../../serial/serial.h"

#include "../../../cpu/timer/timer.h"

#include "../../../libk/string/string.h"

#include "../../../kernel/memory/memory.h"

uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster);

// This Function Returns the Address of the FAT
/*
  While it might seem self explanatory that the bootsector is sector 0,
  This is future proofing for if we ever decide to add partitioning support.
  In a partition, the bpb won't be at lba 0, unless we are the first partition.
*/
void* load_fat(uint32_t bootsector) {
  // Load our BPB
  BPB_t *boot = kmalloc(512);
  ata_read_sector(bootsector, 1, boot);

  // Reserve space for the FAT
  uint32_t *fat = kmalloc((boot->EBPB_SECTORS_PER_FAT*512));
  // Load the FAT
  ata_read_sector(boot->BPB_RESERVED_SECTORS, boot->EBPB_SECTORS_PER_FAT, fat);
  return fat;
}

// Returns the Disk Address of the File Entry when found
uint32_t find_entry(char name[11], uint32_t dir_cluster, uint32_t *fat) {

  DirectoryEntry_t *entryBuffer = kmalloc(512);

  while (dir_cluster < 0x0FFFFFF8) {
    uint32_t currentSector = get_sector_from_cluster(dir_cluster, 1);
    ata_read_sector(currentSector, 1, entryBuffer);
    dir_cluster = fat[dir_cluster];

    for (int i = 0; i < 512 / 32; i++) {
      // Compare the String
      uint8_t a = cmpStr(name, entryBuffer[i].name, 11);
      // If they match, return the disk address of the entry
      if (a) {
        kfree(1024); // Free the memory we used
        return (currentSector * 512) + (i * 32);
      }
    }
  }
  // Return an invalid address if we can't find it.
  kfree(1024);
  return 0xFFFFFFFF;
}

// This function returns the size of an entry given its starting cluster by
// Following the Cluster Chain until it reaches the end
uint32_t get_cluster_size_of_entry(uint32_t cluster, uint32_t *fat) {
  uint32_t clusterCount = 1;
  while (cluster < 0x0FFFFFF8) {
    clusterCount += 1;
    cluster = fat[cluster];
  }
  return clusterCount;
}

// Gets the sector number from a cluster
uint32_t get_sector_from_cluster(uint32_t cluster, uint32_t sectors_per_cluster) {
  return ((cluster - 2) * sectors_per_cluster) + 2050;
}

// Determine if the entry is Unused, Long_File, or Regular, or Dir, Empty Dir
uint8_t parse_entry(DirectoryEntry_t *entry) {
  // Return End of Directory, or Unused Entry
  if ((unsigned char) entry->name[0] == 0) {
    return NO_MORE_ENTRIES_IN_DIRECTORY;
  } else if ((unsigned char) entry->name[0] == 0xE5) {
    return ENTRY_UNUSED;
  }
  // We'll need to check each of these individually

  if (entry->attrib == 0x0F) return LONG_FILE_NAME;
  if (entry->attrib & 16) return DIRECTORY;

  return REGULAR_FILE;
}

// Returns the address of the File.
// TODO: Change this to a file_t
void* load_entry (uint32_t entryAddress, uint32_t* fat) {

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
  uint8_t* fileBuffer = kmalloc(bytesToAllocate);

  while (cluster < 0x0FFFFFF8) {
    fileSector = get_sector_from_cluster(cluster, 1);
    ata_read_sector(fileSector, 1, fileBuffer + (fileSectorOffset*512));
    cluster = fat[cluster];
    fileSectorOffset++;
  }

  return (void*) fileBuffer;

}
