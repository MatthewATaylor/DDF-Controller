#include "game_test.h"

void game_test_init(
    void *game_test,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS]
) {
    struct game_test *game = (struct game_test *) game_test;
    game->color_value = 4;
    game->direction = 4;
}

void game_test_loop(
    void *game_test,
    uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS],
    struct kb *kb,
    float spf
) {
    /* Demo interface with red and blue fading animation */

    struct game_test *game = (struct game_test *) game_test;
    uint8_t i, j;
    uint8_t max_brightness = 240;

    printf("space is pressed: %d\n", kb_read_map(kb->map, KEY_SPACE));

    if (game->color_value == max_brightness || game->color_value == 0) {
        game->direction *= -1;
    }
    game->color_value += game->direction;

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            if (i % 2 == 0) {
                color_frame[i][j][0] = 0;
                color_frame[i][j][1] = game->color_value;
                color_frame[i][j][2] = 0;
            }
            else {
                color_frame[i][j][0] = 0;
                color_frame[i][j][1] = 0;
                color_frame[i][j][2] = max_brightness - game->color_value;
            }
        }
    }
}


