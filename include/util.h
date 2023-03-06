#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <sys/time.h>

uint16_t combine_bytes(uint8_t lsb, uint8_t msb);
double get_millis();

#endif

