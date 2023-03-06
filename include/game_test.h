#ifndef GAME_TEST_H
#define GAME_TEST_H

#include <stdint.h>
#include <stdio.h>

#include "global_defines.h"
#include "kb.h"

struct game_test {
    /* Use the game's struct to store game state info */
    uint8_t color_value;
    int8_t direction;
};

void game_test_init(
    void *game_test,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
);
void game_test_loop(
    void *game_test,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
);

#endif

