#ifndef MANAGER_H
#define MANAGER_H
#include <stdint.h>

void init_memory_manager();
uintptr_t malloc();
void free(uintptr_t pointer);

#endif
