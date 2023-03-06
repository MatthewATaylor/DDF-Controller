#ifndef KB_H
#define KB_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <glob.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "global_defines.h"

struct kb {
    FILE *file;
    char map[KEY_MAX / 8 + 1];
};

int kb_init(struct kb *kb);
void kb_update_map(struct kb *kb);
uint8_t kb_read_map(struct kb *kb, int key_code);
void kb_free(struct kb *kb);

#endif

