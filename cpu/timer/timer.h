#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

// PIT Ticks every Microsecond
#define FREQUENCY 1000

void init_timer(uint32_t freq);

void msleep(uint32_t milliseconds);
void sleep(uint32_t seconds);

#endif
