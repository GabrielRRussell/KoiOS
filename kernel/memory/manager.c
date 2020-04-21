#include <stddef.h>
#include "manager.h"

// Private Prototypes
uintptr_t returnPointerFromBlock(uint32_t block);
uint32_t returnBlockFromPointer(uintptr_t pointer);


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


uintptr_t malloc(void) {
  /*
    We keep track of the current status of the block we read
    The offset is the uint8_t index of our blockMap[]
    The current bit is the bit offset from the index
    So we can get a block by doing (Offset * 8) + Bit
    Then return the block as a pointer
  */
  uint32_t currentBlockSet = 1;
  uint8_t currentBit = 0;
  uint32_t currentOffset = 0;

  while (currentBlockSet == 1) {
    currentOffset++;
    // Iterate through each bit in the byte
    for (currentBit = 1; currentBit < 129; currentBit *= 2) {
      currentBlockSet = (blockMap[currentOffset] & currentBit);
      if (!currentBlockSet) break;
    }
  }

  // If we went through the entire memory map, and didn't find a free block,
  // then just return NULL
  if (currentBlockSet == 0) {
    // We use the currentBit value to AND above, here we convert it
    // to a position to use when setting the memory map we return
    switch (currentBit) {
      case 1:
        currentBit = 0;
        break;
      case 2:
        currentBit = 1;
        break;
      case 4:
        currentBit = 2;
        break;
      case 8:
        currentBit = 3;
        break;
      case 16:
        currentBit = 4;
        break;
      case 32:
        currentBit = 5;
        break;
      case 64:
        currentBit = 6;
        break;
      case 128:
        currentBit = 7;
        break;
    }

    currentOffset *= 8;
    currentOffset += currentBit;
    return returnPointerFromBlock(currentOffset);
  } else {
    return NULL;
  }
}

void free(uintptr_t pointer) {
  uint32_t block = returnBlockFromPointer(pointer);
  uint8_t bit = block % 8;
  block = block - bit;
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
