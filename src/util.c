#include "util.h"

uint16_t combine_bytes(uint8_t lsb, uint8_t msb) {
    return ((uint16_t) lsb) | (((uint16_t) msb) << 8);
}

double get_millis() {
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec * 1000 + t.tv_usec / 1000.0;
}

