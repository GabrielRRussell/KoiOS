#include "manager.h"

uint8_t blockMap[0x20000]; //THIS IS OUR MEMORY MAP
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
    Reserve the first 40960 or 0xA000 bytes for our Operating System by default
    Kernel Loaded to  0x1000
    Stack set     to  0x8000
  */
  for (int i = 0; i < 10; i++) {
    blockMap[i] = (blockMap[i] & 0xFF);
  }
}


uintptr_t malloc(uint8_t blocks) {
  /*
    We keep track of the current status of the block we read
    The offset is the uint8_t index of our blockMap[]
    The current bit is the bit offset from the index
    So we can get a block by doing (Offset * 8) + Bit
    Then return the block as a pointer
  */
  uint8_t currentBlockSet = 0;
  uint8_t currentBit = 0;
  uint32_t currentOffset = 0;

  while (currentBlockSet == 0) {
    currentOffset++;

    for (currentBit; currentBit < 8; currentBit++) {
      currentBlockSet = (blockMap[currentOffset] >> currentBit) & 1;
      if (currentBlockSet) break;
    }

  }
  currentOffset *= 8;
  currentOffset += currentBit;
  return returnPointerFromBlock(currentOffset);

}

uintptr_t returnPointerFromBlock(uint32_t block) {
  return (uintptr_t) (block * 4096);
}
