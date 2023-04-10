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
    },
    0, 255, 255
};
static struct tetris_tetromino tetris_tetromino_j = {
    0,
    {
        {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    0, 0, 255
};
static struct tetris_tetromino tetris_tetromino_l = {
    0,
    {
        {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    255, 64, 0
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

uint8_t tetris_is_collision(
    struct tetris *game,
    int8_t new_x, int8_t new_y, uint8_t new_rotation
) {
    /* Check if the current tetromino position overlaps with an existing tetromino
       Note: must call tetris_clear_tetromino first */

    int8_t i, j;

    for (i = new_y; i < new_y + 4; ++i) {
        for (j = new_x; j < new_x + 4; ++j) {
            if (game->tetrominoes[game->tetromino_index]->shape[new_rotation][i - new_y][j - new_x]) {
                /* Tile filled by current tetromino */
                if (i >= 0 && i < TETRIS_BOARD_H_TILES && j >= 0 && j < TETRIS_BOARD_W_TILES) {
                    /* Tile on game board */
                    if (game->board[i][j] != -1) {
                        /* Tile filled by existing tetromino */
                        return 1;
                    }
                }
                else {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void tetris_clear_tetromino(struct tetris *game) {
    uint8_t i, j;

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (game->tetrominoes[game->tetromino_index]->shape[game->current_rotation][i][j]) {
                game->board[i + game->current_y][j + game->current_x] = -1;
            }
        }
    }
}

void tetris_set_tetromino(struct tetris *game) {
    int8_t i, j;

    for (i = game->current_y; i < game->current_y + 4; ++i) {
        for (j = game->current_x; j < game->current_x + 4; ++j) {
            if (i >= 0 && i < TETRIS_BOARD_H_TILES &&
                    j >= 0 && j < TETRIS_BOARD_W_TILES &&
                    game->tetrominoes[game->tetromino_index]->
                        shape[game->current_rotation][i - game->current_y][j - game->current_x]) {
                game->board[i][j] = game->tetromino_index;
            }
        }
    }
}

void tetris_spawn(struct tetris *game) {
    game->tetromino_index = rand() % 3;

    game->current_x = 3;
    game->current_y = -game->tetrominoes[game->tetromino_index]->y_origin;
    game->current_rotation = 0;

    if (!tetris_is_collision(game, game->current_x, game->current_y, game->current_rotation)) {
        tetris_set_tetromino(game);
    }
}

void tetris_init(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j;
    size_t k;

    for (k = 0; k < KEY_MAX; ++k) {
        game->key_timers[k] = 0;
    }

    for (i = 0; i < TETRIS_BOARD_H_TILES; ++i) {
        for (j = 0; j < TETRIS_BOARD_W_TILES; ++j) {
            game->board[i][j] = -1;
        }
    }

    game->current_x = 0;
    game->current_y = 0;
    game->current_rotation = 0;

    game->tetrominoes[0] = &tetris_tetromino_i;
    game->tetrominoes[1] = &tetris_tetromino_j;
    game->tetrominoes[2] = &tetris_tetromino_l;
    game->tetromino_index = 0;

    srand(time(0));

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

    tetris_spawn(game);
}

void tetris_loop(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j;
    uint8_t new_rotation;

    if (kb_read_map(kb->map, KEY_ENTER)) {
        if (!kb_read_map(kb->prev_map, KEY_ENTER)) {
            tetris_spawn(game);
        }
    }

    tetris_clear_tetromino(game);

    if (kb_read_map(kb->map, KEY_RIGHT)) {
        if (!kb_read_map(kb->prev_map, KEY_RIGHT) ||
                get_millis() - game->key_timers[KEY_RIGHT] > TETRIS_MS_PER_MOVE) {
            if (!tetris_is_collision(game, game->current_x + 1, game->current_y, game->current_rotation)) {
                game->current_x += 1;
                game->key_timers[KEY_RIGHT] = get_millis();
            }
        }
    }
    if (kb_read_map(kb->map, KEY_LEFT)) {
        if (!kb_read_map(kb->prev_map, KEY_LEFT) ||
                get_millis() - game->key_timers[KEY_LEFT] > TETRIS_MS_PER_MOVE) {
            if (!tetris_is_collision(game, game->current_x - 1, game->current_y, game->current_rotation)) {
                game->current_x -= 1;
                game->key_timers[KEY_LEFT] = get_millis();
            }
        }
    }
    if (kb_read_map(kb->map, KEY_UP)) {
        if (!kb_read_map(kb->prev_map, KEY_UP) ||
                get_millis() - game->key_timers[KEY_UP] > TETRIS_MS_PER_MOVE) {
            if (!tetris_is_collision(game, game->current_x, game->current_y - 1, game->current_rotation)) {
                game->current_y -= 1;
                game->key_timers[KEY_UP] = get_millis();
            }
        }
    }
    if (kb_read_map(kb->map, KEY_DOWN)) {
        if (!kb_read_map(kb->prev_map, KEY_DOWN) ||
                get_millis() - game->key_timers[KEY_DOWN] > TETRIS_MS_PER_MOVE) {
            if (!tetris_is_collision(game, game->current_x, game->current_y + 1, game->current_rotation)) {
                game->current_y += 1;
                game->key_timers[KEY_DOWN] = get_millis();
            }
        }
    }

    if (kb_read_map(kb->map, KEY_Z)) {
        if (!kb_read_map(kb->prev_map, KEY_Z) ||
                get_millis() - game->key_timers[KEY_Z] > TETRIS_MS_PER_MOVE) {
            if (game->current_rotation == 0) {
                new_rotation = 3;
            }
            else {
                new_rotation = game->current_rotation - 1;
            }
            if (!tetris_is_collision(game, game->current_x, game->current_y, new_rotation)) {
                game->current_rotation = new_rotation;
                game->key_timers[KEY_Z] = get_millis();
            }
        }
    }
    if (kb_read_map(kb->map, KEY_X)) {
        if (!kb_read_map(kb->prev_map, KEY_X) ||
                get_millis() - game->key_timers[KEY_X] > TETRIS_MS_PER_MOVE) {
            if (game->current_rotation == 3) {
                new_rotation = 0;
            }
            else {
                new_rotation = game->current_rotation + 1;
            }
            if (!tetris_is_collision(game, game->current_x, game->current_y, new_rotation)) {
                game->current_rotation = new_rotation;
                game->key_timers[KEY_X] = get_millis();
            }
        }
    }

    tetris_set_tetromino(game);

    for (i = 0; i < TETRIS_BOARD_H_TILES; ++i) {
        for (j = 0; j < TETRIS_BOARD_W_TILES; ++j) {
            if (game->board[i][j] != -1) {
                tetris_color_tile(
                    color_frame,
                    i, j,
                    game->tetrominoes[game->board[i][j]]->r,
                    game->tetrominoes[game->board[i][j]]->g,
                    game->tetrominoes[game->board[i][j]]->b
                );
            }
            else {
                tetris_color_tile(color_frame, i, j, 0, 0, 0);
            }
        }
    }
}

