#ifndef TETRIS_H
#define TETRIS_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>
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
#define TETRIS_MS_PER_MOVE 250
#define TETRIS_I_INDEX 0
#define TETRIS_J_INDEX 1
#define TETRIS_L_INDEX 2
#define TETRIS_O_INDEX 3
#define TETRIS_S_INDEX 4
#define TETRIS_T_INDEX 5
#define TETRIS_Z_INDEX 6

struct tetris_tetromino {
    uint8_t y_origin;
    uint8_t shape[4][4][4];
    uint8_t r, g, b;
};

struct tetris {
    double key_timers[KEY_MAX];
    
    /* -1: unfilled tile, else: tetromino index */
    int8_t board[TETRIS_BOARD_H_TILES][TETRIS_BOARD_W_TILES];

    int8_t current_x, current_y;
    uint8_t current_rotation;

    struct tetris_tetromino *tetrominoes[7];
    uint8_t tetromino_index;

    /* 1st index: current_rotation, 2nd index: attempt number, 3rd index: x/y */
    int8_t jlstz_wall_kick_inc[4][4][2];
    int8_t jlstz_wall_kick_dec[4][4][2];
    int8_t i_wall_kick_inc[4][4][2];
    int8_t i_wall_kick_dec[4][4][2];
};

void tetris_color_tile(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
);

uint8_t tetris_is_collision(
    struct tetris *game,
    int8_t new_x, int8_t new_y, uint8_t new_rotation
);

void tetris_clear_tetromino(struct tetris *game);

void tetris_set_tetromino(struct tetris *game);

void tetris_spawn(struct tetris *game);

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
