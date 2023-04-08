#include "tetris.h"

static struct tetris_tetromino tetris_tetromino_i = {
    1,
    {
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    }
};

void tetris_color_tile(
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    uint8_t row, uint8_t col,
    uint8_t r, uint8_t g, uint8_t b
) {
    uint8_t i, j;

    for (i = row * TETRIS_TILE_H + TETRIS_BOARD_Y; i < (row + 1) * TETRIS_TILE_H + TETRIS_BOARD_Y; ++i) {
        for (j = col * TETRIS_TILE_W + TETRIS_BOARD_X; j < (col + 1) * TETRIS_TILE_W + TETRIS_BOARD_X; ++j) {
            color_frame[i][j][0] = g;
            color_frame[i][j][1] = r;
            color_frame[i][j][2] = b;
        }
    }
}

void tetris_init(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j;
    size_t k;

    game->tile_x = 0;
    game->tile_y = 0;

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            if (i < TETRIS_BOARD_Y || 
                    i >= TETRIS_BOARD_Y + TETRIS_BOARD_H || 
                    j < TETRIS_BOARD_X || 
                    j >= TETRIS_BOARD_X + TETRIS_BOARD_W) {
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

    for (k = 0; k < KEY_MAX; ++k) {
        game->key_timers[k] = 0;
    }
}

void tetris_loop(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j;

    if (kb_read_map(kb->map, KEY_RIGHT)) {
        if (!kb_read_map(kb->prev_map, KEY_RIGHT) ||
                get_millis() - game->key_timers[KEY_RIGHT] > TETRIS_MS_PER_MOVE) {
            game->tile_x += 1;
            game->key_timers[KEY_RIGHT] = get_millis();
        }
    }
    else if (kb_read_map(kb->map, KEY_LEFT)) {
        if (!kb_read_map(kb->prev_map, KEY_LEFT) ||
                get_millis() - game->key_timers[KEY_LEFT] > TETRIS_MS_PER_MOVE) {
            game->tile_x -= 1;
            game->key_timers[KEY_LEFT] = get_millis();
        }
    }

    if (kb_read_map(kb->map, KEY_UP)) {
        if (!kb_read_map(kb->prev_map, KEY_UP) ||
                get_millis() - game->key_timers[KEY_UP] > TETRIS_MS_PER_MOVE) {
            game->tile_y -= 1;
            game->key_timers[KEY_UP] = get_millis();
        }
    }
    else if (kb_read_map(kb->map, KEY_DOWN)) {
        if (!kb_read_map(kb->prev_map, KEY_DOWN) ||
                get_millis() - game->key_timers[KEY_DOWN] > TETRIS_MS_PER_MOVE) {
            game->tile_y += 1;
            game->key_timers[KEY_DOWN] = get_millis();
        }
    }
   
    if (game->tile_x >= TETRIS_BOARD_W_TILES) {
        game->tile_x = TETRIS_BOARD_W_TILES - 1;
    }
    else if (game->tile_x < 0) {
        game->tile_x = 0;
    }

    if (game->tile_y >= TETRIS_BOARD_H_TILES) {
        game->tile_y = TETRIS_BOARD_H_TILES - 1;
    }
    else if (game->tile_y < 0) {
        game->tile_y = 0;
    }

    for (i = 0; i < TETRIS_BOARD_H_TILES; ++i) {
        for (j = 0; j < TETRIS_BOARD_W_TILES; ++j) {
            if (i == game->tile_y && j == game->tile_x) {
                tetris_color_tile(color_frame, i, j, 0, 255, 0);
            }
            else {
                tetris_color_tile(color_frame, i, j, 0, 0, 0);
            }
        }
    }
}

