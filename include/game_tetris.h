#ifndef GAME_TETRIS_H
#define GAME_TETRIS_H

#include <stdint.h>
#include <math.h>

#include "global_defines.h"
#include "kb.h"

struct game_tetris {
    float square_x;
    float square_y;
};

void game_tetris_color_pixel(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
);

void game_tetris_init(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
);
void game_tetris_loop(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
);

#endif

