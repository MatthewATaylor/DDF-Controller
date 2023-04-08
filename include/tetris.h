#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <linux/input.h>

#include "global_defines.h"
#include "util.h"
#include "kb.h"

#define TETRIS_TILE_W 6
#define TETRIS_TILE_H 3
#define TETRIS_BOARD_X 52
#define TETRIS_BOARD_Y 6
#define TETRIS_BOARD_W 60
#define TETRIS_BOARD_H 60
#define TETRIS_BOARD_W_TILES 10
#define TETRIS_BOARD_H_TILES 20
#define TETRIS_MS_PER_MOVE 175

struct tetris_tetromino {
    uint8_t y_origin;
    uint8_t shape[4][4][4];
};

struct tetris {
    int8_t tile_x;
    int8_t tile_y;
    double key_timers[KEY_MAX];
    uint8_t board[TETRIS_BOARD_H_TILES][TETRIS_BOARD_W_TILES];
    int8_t current_x;
    int8_t current_y;
    struct tetris_tetromino *current_tetromino;
};

void tetris_color_tile(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
);

void tetris_init(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
);
void tetris_loop(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
);

#endif

