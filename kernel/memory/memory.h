#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

void* kmalloc_f(uint32_t bytes, uint8_t align);
void* kmalloc(uint32_t bytes);
void* kmalloc_align(uint32_t bytes);

void  kfree(uint32_t bytes);

#endif
