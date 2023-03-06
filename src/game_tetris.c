#include "game_tetris.h"

void game_tetris_init(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct game_tetris *game = (struct game_tetris *) game_tetris;

    game->square_x = 0;
    game->square_y = 0;
}

void game_tetris_loop(
    void *game_tetris,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb
) {

}

