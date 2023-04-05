#include "game_tetris.h"

#define TILE_W 6
#define TILE_H 3
#define BOARD_X 52
#define BOARD_Y 6
#define BOARD_W 60
#define BOARD_H 60
#define BOARD_W_TILES 10
#define BOARD_H_TILES 20
#define MS_PER_MOVE 175

void game_tetris_color_tile(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
) {
    uint8_t i, j;

    for (i = row * TILE_H + BOARD_Y; i < (row + 1) * TILE_H + BOARD_Y; ++i) {
        for (j = col * TILE_W + BOARD_X; j < (col + 1) * TILE_W + BOARD_X; ++j) {
            color_frame[i][j][0] = g;
            color_frame[i][j][1] = r;
            color_frame[i][j][2] = b;
        }
    }
}

void game_tetris_init(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct game_tetris *game = (struct game_tetris *) game_tetris;
    uint8_t i, j;

    game->tile_x = 0;
    game->tile_y = 0;
    game->key_timer = 0;

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            if (i < BOARD_Y || i >= BOARD_Y + BOARD_H || j < BOARD_X || j >= BOARD_X + BOARD_W) {
                color_frame[i][j][0] = 50;
                color_frame[i][j][1] = 50;
                color_frame[i][j][2] = 50;
            }
            else {
                color_frame[i][j][0] = 0;
                color_frame[i][j][1] = 0;
                color_frame[i][j][2] = 0;
            }
        }
    }

}

void game_tetris_loop(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
) {
    struct game_tetris *game = (struct game_tetris *) game_tetris;
    uint8_t i, j;

    if (kb_read_map(kb->map, KEY_RIGHT)) {
        if (!kb_read_map(kb->prev_map, KEY_RIGHT) || get_millis() - game->key_timer > MS_PER_MOVE) {
            game->tile_x += 1;
            game->key_timer = get_millis();
        }
    }
    else if (kb_read_map(kb->map, KEY_LEFT)) {
        if (!kb_read_map(kb->prev_map, KEY_LEFT) || get_millis() - game->key_timer > MS_PER_MOVE) {
            game->tile_x -= 1;
            game->key_timer = get_millis();
        }
    }

    if (kb_read_map(kb->map, KEY_UP)) {
        if (!kb_read_map(kb->prev_map, KEY_UP) || get_millis() - game->key_timer > MS_PER_MOVE) {
            game->tile_y -= 1;
            game->key_timer = get_millis();
        }
    }
    else if (kb_read_map(kb->map, KEY_DOWN)) {
        if (!kb_read_map(kb->prev_map, KEY_DOWN) || get_millis() - game->key_timer > MS_PER_MOVE) {
            game->tile_y += 1;
            game->key_timer = get_millis();
        }
    }
   

    if (game->tile_x >= BOARD_W_TILES) {
        game->tile_x = BOARD_W_TILES - 1;
    }
    else if (game->tile_x < 0) {
        game->tile_x = 0;
    }

    if (game->tile_y >= BOARD_H_TILES) {
        game->tile_y = BOARD_H_TILES - 1;
    }
    else if (game->tile_y < 0) {
        game->tile_y = 0;
    }

   

    for (i = 0; i < BOARD_H_TILES; ++i) {
        for (j = 0; j < BOARD_W_TILES; ++j) {
            if (i == game->tile_y && j == game->tile_x) {
                game_tetris_color_tile(color_frame, i, j, 0, 255, 0);
            }
            else {
                game_tetris_color_tile(color_frame, i, j, 0, 0, 0);
            }
        }
    }
}

