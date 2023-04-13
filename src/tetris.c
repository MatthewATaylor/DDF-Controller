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
    255, 40, 0
};
static struct tetris_tetromino tetris_tetromino_o = {
    0,
    {
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    255, 150, 0
};
static struct tetris_tetromino tetris_tetromino_s = {
    0,
    {
        {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    0, 255, 0
};
static struct tetris_tetromino tetris_tetromino_t = {
    0,
    {
        {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    128, 0, 255
};
static struct tetris_tetromino tetris_tetromino_z = {
    0,
    {
        {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    255, 0, 0
};

static uint8_t digit_pixels[10][5][3] = {
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
    },
    {
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
    },
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    },
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
    },
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1}
    },
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
    }
};

void tetris_animate_bg(
    struct tetris *game,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    uint8_t i, j;
    uint16_t adj_i;
    float cos_1, cos_2, cos_3;

    game->bg_offset += (get_millis() - game->bg_prev_time) / 10.0;
    while (game->bg_offset >= LED_ROWS) {
        game->bg_offset -= LED_ROWS;
    }
    game->bg_prev_time = get_millis();
    
    for (i = 0; i < LED_ROWS; ++i) {
        cos_1 = cos(M_PI * (3 * i / (float) LED_ROWS));
        cos_2 = cos(M_PI * 3 * (i - LED_ROWS / 3.0f) / (float) LED_ROWS);
        cos_3 = cos(M_PI * 3 * (i - 2 * LED_ROWS / 3.0f) / (float) LED_ROWS);

        adj_i = i + (uint8_t) game->bg_offset;
        if (adj_i >= LED_ROWS) {
            adj_i -= LED_ROWS;
        }

        for (j = 0; j < LED_COLS; ++j) {
            if (adj_i < TETRIS_BOARD_Y || adj_i >= TETRIS_BOARD_Y + TETRIS_BOARD_H ||
                    j < TETRIS_BOARD_X || j >= TETRIS_BOARD_X + TETRIS_BOARD_W) {
                if (i < LED_ROWS / 3) {
                    color_frame[adj_i][j][0] = -TETRIS_BG_LEVEL * cos_1 + TETRIS_BG_LEVEL;
                    color_frame[adj_i][j][1] =  TETRIS_BG_LEVEL * cos_1 + TETRIS_BG_LEVEL;
                    color_frame[adj_i][j][2] =  0;
                }
                else if (i < 2 * LED_ROWS / 3) {
                    color_frame[adj_i][j][0] =  TETRIS_BG_LEVEL * cos_2 + TETRIS_BG_LEVEL;
                    color_frame[adj_i][j][1] =  0;
                    color_frame[adj_i][j][2] = -TETRIS_BG_LEVEL * cos_2 + TETRIS_BG_LEVEL;
                }
                else {
                    color_frame[adj_i][j][0] =  0;
                    color_frame[adj_i][j][1] = -TETRIS_BG_LEVEL * cos_3 + TETRIS_BG_LEVEL;
                    color_frame[adj_i][j][2] =  TETRIS_BG_LEVEL * cos_3 + TETRIS_BG_LEVEL;
                }
            }
            else {
                color_frame[adj_i][j][0] = 0;
                color_frame[adj_i][j][1] = 0;
                color_frame[adj_i][j][2] = 0;
            }
        }
    }

    for (j = 0; j < 3; ++j) {
        for (i = TETRIS_BOARD_Y - 1; i <= TETRIS_BOARD_Y + TETRIS_BOARD_H; ++i) {
            color_frame[i][TETRIS_BOARD_X - 1][j] = TETRIS_BG_LEVEL;
            color_frame[i][TETRIS_BOARD_X + TETRIS_BOARD_W][j] = TETRIS_BG_LEVEL;
        }
        for (i = TETRIS_BOARD_X - 1; i <= TETRIS_BOARD_X + TETRIS_BOARD_W; ++i) {
            color_frame[TETRIS_BOARD_Y - 1][i][j] = TETRIS_BG_LEVEL * (i % 2);
            color_frame[TETRIS_BOARD_Y + TETRIS_BOARD_H][i][j] = TETRIS_BG_LEVEL * (i % 2);
        }
    }
}

void tetris_draw_scoreboard(
    struct tetris *game,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    uint8_t i, j, k, l, m, n;
    uint8_t digit;
    uint32_t score = game->score;
    uint32_t score_1 = game->paddle_1_score;
    uint32_t score_2 = game->paddle_2_score;
    uint8_t score_pixel_x, score_pixel_y;

    for (j = 0; j < 3; ++j) {
        for (i = TETRIS_SCORE_Y - 2; i <= TETRIS_SCORE_Y + TETRIS_SCORE_H + 1; ++i) {
            color_frame[i][TETRIS_SCORE_X - 2][j] = TETRIS_BG_LEVEL;
            color_frame[i][TETRIS_SCORE_X + TETRIS_SCORE_W + 1][j] = TETRIS_BG_LEVEL;
        }
        for (i = TETRIS_SCORE_X - 2; i <= TETRIS_SCORE_X + TETRIS_SCORE_W + 1; ++i) {
            color_frame[TETRIS_SCORE_Y - 2][i][j] = TETRIS_BG_LEVEL * (i % 2);
            color_frame[TETRIS_SCORE_Y + TETRIS_SCORE_H + 1][i][j] = TETRIS_BG_LEVEL * (i % 2);
        }
    }

    for (i = TETRIS_SCORE_Y - 1; i <= TETRIS_SCORE_Y + TETRIS_SCORE_H; ++i) {
        for (j = TETRIS_SCORE_X - 1; j <= TETRIS_SCORE_X + TETRIS_SCORE_W; ++j) {
            for (k = 0; k < 3; ++k) {
                color_frame[i][j][k] = 0;
            }
        }
    }

    for (i = 0; i < 4; ++i) {
        if (game->is_pong) {
            if (i < 2) {
                digit = score_2 % 10;
                score_2 /= 10;
            }
            else {
                digit = score_1 % 10;
                score_1 /= 10;
            }
        }
        else {
            digit = score % 10;
            score /= 10;
        }

        /* Loop over digit_pixels */
        for (j = 0; j < 5; ++j) {
            for (k = 0; k < 3; ++k) {
                /* Loop over the area each element in digit_pixels takes up */
                for (l = 0; l < 2; ++l) {
                    for (m = 0; m < 3; ++m) {
                        score_pixel_x = TETRIS_SCORE_X + (3 - i) * 10 + k * 3 + m;
                        score_pixel_y = TETRIS_SCORE_Y + j * 2 + l;

                        if (game->is_pong) {
                            color_frame[score_pixel_y][score_pixel_x][0] = 0;
                            color_frame[score_pixel_y][score_pixel_x][1] = 
                                100 * digit_pixels[digit][j][k] * (i < 2);
                            color_frame[score_pixel_y][score_pixel_x][2] = 
                                100 * digit_pixels[digit][j][k] * (i >= 2);
                        }
                        else {
                            /* Loop over color channels */
                            for (n = 0; n < 3; ++n) {
                                color_frame[score_pixel_y][score_pixel_x][n] = 
                                    TETRIS_BG_LEVEL * digit_pixels[digit][j][k];
                            }
                        }
                    }
                }
            }
        }
    }
}

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

void tetris_clear_rows(struct tetris *game) {
    uint8_t i, j, k, l;
    uint8_t rows_cleared = 0;

    for (i = 0; i < TETRIS_BOARD_H_TILES; ++i) {
        for (j = 0; j < TETRIS_BOARD_W_TILES; ++j) {
            if (game->board[i][j] == -1) {
                break;
            }
            else {
                if (j == TETRIS_BOARD_W_TILES - 1) {
                    /* Row is full - shift tiles down */
                    for (k = i; k > 0; --k) {
                        for (l = 0; l < TETRIS_BOARD_W_TILES; ++l) {
                            game->board[k][l] = game->board[k - 1][l];
                        }
                    }
                    ++rows_cleared;
                }
            }
        }  
    }

    if (rows_cleared) {
        game->score += rows_cleared * pow(2, rows_cleared - 1);
        game->rows_cleared += rows_cleared;
    }
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

void tetris_reset(struct tetris *game) {
    uint8_t i, j;

    for (i = 0; i < TETRIS_BOARD_H_TILES; ++i) {
        for (j = 0; j < TETRIS_BOARD_W_TILES; ++j) {
            game->board[i][j] = -1;
        }
    }

    game->game_has_started = 0;
}

void tetris_spawn(struct tetris *game) {
    game->tetromino_index = rand() % 7;

    game->current_x = 3;
    game->current_y = -game->tetrominoes[game->tetromino_index]->y_origin;
    game->current_rotation = 0;

    if (!tetris_is_collision(game, game->current_x, game->current_y, game->current_rotation)) {
        tetris_set_tetromino(game);
    }
    else {
        tetris_reset(game);
    }
}

void tetris_pong_pos_reset(struct tetris *game, int8_t server) {
    game->paddle_1_x = TETRIS_BOARD_X + TETRIS_BOARD_W / 2.0f - TETRIS_PADDLE_W / 2.0f;
    game->paddle_2_x = TETRIS_BOARD_X + TETRIS_BOARD_W / 2.0f - TETRIS_PADDLE_W / 2.0f;

    game->ball_x = TETRIS_BOARD_X + TETRIS_BOARD_W / 2.0f - TETRIS_BALL_W / 2.0f;
    game->ball_y = TETRIS_BOARD_Y + TETRIS_BOARD_H / 2.0f - TETRIS_BALL_H / 2.0f;
    game->ball_theta = server * M_PI / 2.0f;

    game->serve_is_waiting = 1;
}

void tetris_init(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j;
    size_t k;

    int8_t jlstz_wall_kick_inc[4][4][2] = {
        { {-1,  0}, {-1,  1}, { 0, -2}, {-1, -2} },
        { { 1,  0}, { 1, -1}, { 0,  2}, { 1,  2} },
        { { 1,  0}, { 1,  1}, { 0, -2}, { 1, -2} },
        { {-1,  0}, {-1, -1}, { 0,  2}, {-1,  2} }
    };
    int8_t jlstz_wall_kick_dec[4][4][2] = {
        { { 1,  0}, { 1,  1}, { 0, -2}, { 1, -2} },
        { { 1,  0}, { 1, -1}, { 0,  2}, { 1,  2} },
        { {-1,  0}, {-1,  1}, { 0, -2}, {-1, -2} },
        { {-1,  0}, {-1, -1}, { 0,  2}, {-1,  2} }
    };
    int8_t i_wall_kick_inc[4][4][2] = {
        { {-2,  0}, { 1,  0}, {-2, -1}, { 1,  2} },
        { {-1,  0}, { 2,  0}, {-1,  2}, { 2, -1} },
        { { 2,  0}, {-1,  0}, { 2,  1}, {-1, -2} },
        { { 1,  0}, {-2,  0}, { 1, -2}, {-2,  1} }
    };
    int8_t i_wall_kick_dec[4][4][2] = {
        { {-1,  0}, { 2,  0}, {-1,  2}, { 2, -1} },
        { { 2,  0}, {-1,  0}, { 2,  1}, {-1, -2} },
        { { 1,  0}, {-2,  0}, { 1, -2}, {-2,  1} },
        { {-2,  0}, { 1,  0}, {-2, -1}, { 1,  2} }
    };

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

    game->tetrominoes[TETRIS_I_INDEX] = &tetris_tetromino_i;
    game->tetrominoes[TETRIS_J_INDEX] = &tetris_tetromino_j;
    game->tetrominoes[TETRIS_L_INDEX] = &tetris_tetromino_l;
    game->tetrominoes[TETRIS_O_INDEX] = &tetris_tetromino_o;
    game->tetrominoes[TETRIS_S_INDEX] = &tetris_tetromino_s;
    game->tetrominoes[TETRIS_T_INDEX] = &tetris_tetromino_t;
    game->tetrominoes[TETRIS_Z_INDEX] = &tetris_tetromino_z;

    game->tetromino_index = 0;

    game->bg_offset = 0;
    game->bg_prev_time = get_millis();

    srand(time(0));

    memcpy(game->jlstz_wall_kick_inc, jlstz_wall_kick_inc, sizeof(int8_t) * 4 * 4 * 2);
    memcpy(game->jlstz_wall_kick_dec, jlstz_wall_kick_dec, sizeof(int8_t) * 4 * 4 * 2);
    memcpy(game->i_wall_kick_inc, i_wall_kick_inc, sizeof(int8_t) * 4 * 4 * 2);
    memcpy(game->i_wall_kick_dec, i_wall_kick_dec, sizeof(int8_t) * 4 * 4 * 2);

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            color_frame[i][j][0] = 0;
            color_frame[i][j][1] = 0;
            color_frame[i][j][2] = 0;
        }
    }

    game->prev_drop_time = get_millis();
    game->game_has_started = 0;
    game->score = 0;
    game->rows_cleared = 0;

    tetris_pong_pos_reset(game, 1);
    game->paddle_1_score = 0;
    game->paddle_2_score = 0;
}

void tetris_loop(
    void *tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
) {
    struct tetris *game = (struct tetris *) tetris;
    uint8_t i, j, k;
    uint8_t new_rotation;
    int8_t (*wall_kick)[4][2];
    double ms_per_drop;
    uint8_t is_drop_end = 0;

    uint8_t paddle_1_x, paddle_2_x;
    uint8_t ball_x, ball_y;
    float ball_vx, ball_vy;
    float hit_fraction_right;

    tetris_animate_bg(game, color_frame);
    tetris_draw_scoreboard(game, color_frame);

    if (game->is_pong) {
        /* Yes, this is terrible - but I need sleeeeeeep */

        paddle_1_x = (uint8_t) game->paddle_1_x;
        paddle_2_x = (uint8_t) game->paddle_2_x;

        ball_x = (uint8_t) game->ball_x;
        ball_y = (uint8_t) game->ball_y;

        for (i = TETRIS_BOARD_Y; i < TETRIS_BOARD_Y + TETRIS_BOARD_H; ++i) {
            for (j = TETRIS_BOARD_X; j < TETRIS_BOARD_X + TETRIS_BOARD_W; ++j) {
                if (i >= ball_y && i < ball_y + TETRIS_BALL_H &&
                        j >= ball_x && j < ball_x + TETRIS_BALL_W) {
                    for (k = 0; k < 3; ++k) {
                        color_frame[i][j][k] = 180;
                    }
                }
            }
        }

        for (i = 0; i < TETRIS_PADDLE_H; ++i) {
            for (j = TETRIS_BOARD_X; j < TETRIS_BOARD_X + TETRIS_BOARD_W; ++j) {
                if (j >= paddle_2_x && j < paddle_2_x + TETRIS_PADDLE_W) {
                    color_frame[TETRIS_BOARD_Y + i][j][0] = 0;
                    color_frame[TETRIS_BOARD_Y + i][j][1] = 255;
                    color_frame[TETRIS_BOARD_Y + i][j][2] = 0;
                }
                if (j >= paddle_1_x && j < paddle_1_x + TETRIS_PADDLE_W) {
                    color_frame[TETRIS_BOARD_Y + TETRIS_BOARD_H - TETRIS_PADDLE_H + i][j][0] = 0;
                    color_frame[TETRIS_BOARD_Y + TETRIS_BOARD_H - TETRIS_PADDLE_H + i][j][1] = 0;
                    color_frame[TETRIS_BOARD_Y + TETRIS_BOARD_H - TETRIS_PADDLE_H + i][j][2] = 255;
                }
            }
        }

        if (game->serve_is_waiting) {
            /* Start game with space */
            if (kb_read_map(kb->map, KEY_SPACE)) {
                game->serve_is_waiting = 0;
            }
        }
        else {
            /* Stop game with escape */
            if (kb_read_map(kb->map, KEY_ESC)) {
                game->paddle_1_score = 0;
                game->paddle_2_score = 0;
                tetris_pong_pos_reset(game, 1);
            }
        }

        if (kb_read_map(kb->map, KEY_W)) {
            game->paddle_1_x -= spf * TETRIS_PADDLE_SPEED;
        }
        if (kb_read_map(kb->map, KEY_S)) {
            game->paddle_1_x += spf * TETRIS_PADDLE_SPEED;
        }

        if (kb_read_map(kb->map, KEY_UP)) {
            game->paddle_2_x -= spf * TETRIS_PADDLE_SPEED;
        }
        if (kb_read_map(kb->map, KEY_DOWN)) {
            game->paddle_2_x += spf * TETRIS_PADDLE_SPEED;
        }

        if (game->paddle_1_x < TETRIS_BOARD_X) {
            game->paddle_1_x = TETRIS_BOARD_X;
        }
        if (game->paddle_1_x > TETRIS_BOARD_X + TETRIS_BOARD_W - TETRIS_PADDLE_W) {
            game->paddle_1_x = TETRIS_BOARD_X + TETRIS_BOARD_W - TETRIS_PADDLE_W;
        }
        if (game->paddle_2_x < TETRIS_BOARD_X) {
            game->paddle_2_x = TETRIS_BOARD_X;
        }
        if (game->paddle_2_x > TETRIS_BOARD_X + TETRIS_BOARD_W - TETRIS_PADDLE_W) {
            game->paddle_2_x = TETRIS_BOARD_X + TETRIS_BOARD_W - TETRIS_PADDLE_W;
        }

        ball_vx = TETRIS_BALL_SPEED * cos(game->ball_theta);
        ball_vy = TETRIS_BALL_SPEED * sin(game->ball_theta);

        if (!game->serve_is_waiting) {
            game->ball_x += 2 * spf * ball_vx;
            game->ball_y -= spf * ball_vy;
        }

        paddle_1_x = (uint8_t) game->paddle_1_x;
        paddle_2_x = (uint8_t) game->paddle_2_x;

        ball_x = (uint8_t) game->ball_x;
        ball_y = (uint8_t) game->ball_y;

        if (game->ball_y < TETRIS_BOARD_Y) {
            ++game->paddle_1_score;
            tetris_pong_pos_reset(game, -1);
        }
        else if (game->ball_y + TETRIS_BALL_H > TETRIS_BOARD_Y + TETRIS_BOARD_H) {
            ++game->paddle_2_score;
            tetris_pong_pos_reset(game, 1);
        }
        else if (game->ball_x + TETRIS_BALL_W > game->paddle_1_x &&
                game->ball_x < game->paddle_1_x + TETRIS_PADDLE_W &&
                game->ball_y + TETRIS_BALL_H > TETRIS_BOARD_Y + TETRIS_BOARD_H - TETRIS_PADDLE_H) {
            hit_fraction_right = 
                (game->ball_x + TETRIS_BALL_W - game->paddle_1_x) /
                    (float) (TETRIS_PADDLE_W + TETRIS_BALL_W);
            game->ball_theta = (M_PI - 2 * TETRIS_MIN_ANGLE) * (1 - hit_fraction_right) + TETRIS_MIN_ANGLE;
        }
        else if (game->ball_x + TETRIS_BALL_W > game->paddle_2_x &&
                game->ball_x < game->paddle_2_x + TETRIS_PADDLE_W &&
                game->ball_y < TETRIS_BOARD_Y + TETRIS_PADDLE_H ) {
            hit_fraction_right = 
                (game->ball_x + TETRIS_BALL_W - game->paddle_2_x) /
                    (float) (TETRIS_PADDLE_W + TETRIS_BALL_W);
            game->ball_theta = -(M_PI - 2 * TETRIS_MIN_ANGLE) * (1 - hit_fraction_right) - TETRIS_MIN_ANGLE;
        }
        else if (game->ball_x < TETRIS_BOARD_X) {
            game->ball_theta = M_PI - game->ball_theta;
            game->ball_x = TETRIS_BOARD_X;
        }
        else if (game->ball_x + TETRIS_BALL_W > TETRIS_BOARD_X + TETRIS_BOARD_W) {
            game->ball_theta = M_PI - game->ball_theta;
            game->ball_x = TETRIS_BOARD_X + TETRIS_BOARD_W - TETRIS_BALL_W;
        }

        return;
    }

    if (!game->game_has_started) {
        /* Start game with right shift */
        if (kb_read_map(kb->map, KEY_RIGHTSHIFT)) {
            game->game_has_started = 1;
            game->score = 0;
            game->rows_cleared = 0;
            game->prev_drop_time = get_millis();
            tetris_spawn(game);
        }
        else {
            return;
        }
    }
    else {
        /* Stop game with escape */
        if (kb_read_map(kb->map, KEY_ESC)) {
            tetris_reset(game);
            return;
        }
    }

    tetris_clear_tetromino(game);

    /*
    if (kb_read_map(kb->map, KEY_LEFTSHIFT)) {
        if (!kb_read_map(kb->prev_map, KEY_LEFTSHIFT)) {
            ++game->score;
            ++game->rows_cleared;
        }
    }
    */

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

    if (game->tetromino_index != TETRIS_O_INDEX) {
        if (kb_read_map(kb->map, KEY_Z)) {
            if (!kb_read_map(kb->prev_map, KEY_Z) ||
                    get_millis() - game->key_timers[KEY_Z] > TETRIS_MS_PER_MOVE) {
                if (game->tetromino_index == TETRIS_I_INDEX) {
                    wall_kick = game->i_wall_kick_dec;
                }
                else {
                    wall_kick = game->jlstz_wall_kick_dec;
                }

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
                else {
                    for (i = 0; i < 4; ++i) {
                        /* Attempt each wall kick option */
                        if (!tetris_is_collision(
                                game,
                                game->current_x + wall_kick[game->current_rotation][i][0],
                                game->current_y - wall_kick[game->current_rotation][i][1],
                                new_rotation)) {
                            game->current_x += wall_kick[game->current_rotation][i][0];
                            game->current_y -= wall_kick[game->current_rotation][i][1];
                            game->current_rotation = new_rotation;
                            game->key_timers[KEY_Z] = get_millis();
                            break;
                        }
                    }
                }
            }
        }
        if (kb_read_map(kb->map, KEY_X)) {
            if (!kb_read_map(kb->prev_map, KEY_X) ||
                    get_millis() - game->key_timers[KEY_X] > TETRIS_MS_PER_MOVE) {
                if (game->tetromino_index == TETRIS_I_INDEX) {
                    wall_kick = game->i_wall_kick_inc;
                }
                else {
                    wall_kick = game->jlstz_wall_kick_inc;
                }

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
                else {
                    for (i = 0; i < 4; ++i) {
                        /* Attempt each wall kick option */
                        if (!tetris_is_collision(
                                game,
                                game->current_x + wall_kick[game->current_rotation][i][0],
                                game->current_y - wall_kick[game->current_rotation][i][1],
                                new_rotation)) {
                            game->current_x += wall_kick[game->current_rotation][i][0];
                            game->current_y -= wall_kick[game->current_rotation][i][1];
                            game->current_rotation = new_rotation;
                            game->key_timers[KEY_X] = get_millis();
                            break;
                        }
                    }

                }
            }
        }
    }

    if (kb_read_map(kb->map, KEY_SPACE)) {
        if (!kb_read_map(kb->prev_map, KEY_SPACE)) {
            while (!tetris_is_collision(game, game->current_x, game->current_y + 1, game->current_rotation)) {
                game->current_y += 1;
            }
        }
    }

    ms_per_drop = TETRIS_BASE_MS_PER_DROP;

    ms_per_drop -= game->rows_cleared * 13;
    if (ms_per_drop < 35) {
        ms_per_drop = 35;
    }

    if (kb_read_map(kb->map, KEY_DOWN)) {
        if (ms_per_drop / 5.0 > 50) {
            ms_per_drop /= 5.0;
        }
        else {
            ms_per_drop = fmin(ms_per_drop, 100);
        }
    }

    if (get_millis() - game->prev_drop_time > ms_per_drop) {
        game->prev_drop_time = get_millis();
        if (!tetris_is_collision(game, game->current_x, game->current_y + 1, game->current_rotation)) {
            game->current_y += 1;
        }
        else {
            tetris_set_tetromino(game);
            tetris_clear_rows(game);
            tetris_spawn(game);
            is_drop_end = 1;
        }
    }

    if (!is_drop_end) {
        tetris_set_tetromino(game);
    }

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

