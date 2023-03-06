#include "kb.h"

int kb_init(struct kb *kb) {
    memset(kb->prev_map, 0, sizeof(kb->prev_map));
    memset(kb->map, 0, sizeof(kb->map));

    /* Open keyboard device (must be run as root) */
    if (!(kb->file = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r"))) {
        perror("Error [fopen kb]");
        return ERROR_OUT;
    }

    return SUCC_OUT;
}

void kb_update_map(struct kb *kb) {
    memcpy(kb->prev_map, kb->map, sizeof(kb->map));
    memset(kb->map, 0, sizeof(kb->map));
    ioctl(fileno(kb->file), EVIOCGKEY(sizeof(kb->map)), kb->map);
}

uint8_t kb_read_map(char map[KEY_MAX / 8 + 1], int key_code) {
    return (map[key_code / 8] & (1U << (key_code % 8))) > 0;
}

void kb_free(struct kb *kb) {
    fclose(kb->file);
}

