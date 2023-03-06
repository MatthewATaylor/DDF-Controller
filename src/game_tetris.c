#include "game_tetris.h"

#define SQUARE_W 6
#define SQUARE_H 3
#define BOARD_X 52
#define BOARD_Y 6
#define BOARD_W 60
#define BOARD_H 60

void game_tetris_color_pixel(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
) {
    color_frame[row + BOARD_Y][col + BOARD_X][0] = g;
    color_frame[row + BOARD_Y][col + BOARD_X][1] = r;
    color_frame[row + BOARD_Y][col + BOARD_X][2] = b;
}

void game_tetris_init(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct game_tetris *game = (struct game_tetris *) game_tetris;
    uint8_t i, j;

    game->square_x = 0;
    game->square_y = 0;

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            if (i < BOARD_Y || i > BOARD_Y + BOARD_H || j < BOARD_X || j > BOARD_X + BOARD_W) {
                color_frame[i][j][0] = 100;
                color_frame[i][j][1] = 100;
                color_frame[i][j][2] = 100;
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
    uint8_t x, y;

    if (kb_read_map(kb->map, KEY_RIGHT) && !kb_read_map(kb->prev_map, KEY_RIGHT)) {
        game->square_x += SQUARE_W;
    }
    else if (kb_read_map(kb->map, KEY_LEFT) && !kb_read_map(kb->prev_map, KEY_LEFT)) {
        game->square_x -= SQUARE_W;
    }

    if (game->square_x + SQUARE_W >= BOARD_W) {
        game->square_x = BOARD_W - SQUARE_W;
    }
    else if (game->square_x < 0) {
        game->square_x = 0;
    }

    x = (uint8_t) roundf(game->square_x);
    y = (uint8_t) roundf(game->square_y);

    for (i = 0; i < BOARD_H; ++i) {
        for (j = 0; j < BOARD_W; ++j) {
            if (i >= y && i < y + SQUARE_H && j >= x && j < x + SQUARE_W) {
                game_tetris_color_pixel(color_frame, i, j, 255, 255, 255);
            }
            else {
                game_tetris_color_pixel(color_frame, i, j, 0, 0, 0);
            }
        }
    }

    printf("square x: %d\n", x);
}

