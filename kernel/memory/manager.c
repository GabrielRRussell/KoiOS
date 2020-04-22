#include <stddef.h>
#include "manager.h"

// Private Prototypes
uintptr_t returnPointerFromBlock(uint32_t block);
uint32_t returnBlockFromPointer(uintptr_t pointer);


uint8_t blockMap[131072]; //THIS IS OUR MEMORY MAP
                              //
/*
  One bit is equal to 4KB set.
  Meaning if the bit is set, that 4KB is unavailable
  Otherwise, it's free
  There's no ownership scheme. So technically free() can free any block
  This would be a really bad idea for our kernel, but this would be fixed later
  with paging. We don't want it to say, free space from our kernel, and put
  its own data / malicious code there.
*/
void init_memory_manager() {
  /*
    We reserve the first 32 blocks by default
    Kernel Loaded to  0x1000
    Stack set     to  0x8000
  */
  for (int i = 0; i < 4; i++) {
    blockMap[i] = 255;
  }
}


uintptr_t malloc(void) {
  // TODO: Allow to reserve multiple blocks at once

  /*
    We keep track of the current status of the block we read
    The offset is the uint8_t index of our blockMap[]
    The current bit is the bit offset from the index
    So we can get a block by doing (Offset * 8) + Bit
    Then return the block as a pointer
  */
  uint32_t currentBlockSet = 1;
  uint8_t currentBit = 0;
  uint32_t currentOffset = 4;
  // We set the offset to 4 since we reserved the first few blocks for our OS.
  // This cuts down considerably on search time.


  // Right now this will infinitely search, until we find a free block.
  // TODO: add a timeout

  // We want to search for a block not set
  while (currentBlockSet) {
    currentOffset++;
    // Iterate through each bit in the byte
    for (currentBit = 0; currentBit < 8; currentBit++) {
      // Read the current bit, break if it's not set
      currentBlockSet = (blockMap[currentOffset] & (1 << currentBit));
      if (currentBlockSet == 0) {
        // Set the block and break
        blockMap[currentOffset] |= (1 << currentBit);
        break;

      }
    }
  }

  // Return the block address
  // (offset*8 + bit) * 4096
  currentOffset *= 8;
  currentOffset += currentBit;
  return returnPointerFromBlock(currentOffset);
}

void free(uintptr_t pointer) {
  uint32_t block = returnBlockFromPointer(pointer);
  uint8_t bit = block % 8;
  block -= bit;
  blockMap[block] = blockMap[block] & ~(1 << bit);
  return;
}

uintptr_t returnPointerFromBlock(uint32_t block) {
  return (uintptr_t) (block * 4096);
}

uint32_t returnBlockFromPointer(uintptr_t pointer) {
  return (uint32_t) pointer / 4096;
  // uint8_t bit = block % 8;
  // Do this conversion when you get the value back
}
