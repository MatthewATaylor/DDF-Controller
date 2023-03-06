#ifndef GAME_TETRIS_H
#define GAME_TETRIS_H

#include <stdint.h>

#include "global_defines.h"
#include "kb.h"

struct game_tetris {
    uint8_t square_x;
    uint8_t square_y;
};

void game_tetris_init(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
);
void game_tetris_loop(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb
);

#endif

