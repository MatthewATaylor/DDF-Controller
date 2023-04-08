#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <math.h>
#include <pthread.h>

#include "global_defines.h"
#include "util.h"
#include "gif.h"
#include "kb.h"
#include "game_test.h"
#include "tetris.h"

#define DO_ETH 1
#define INTERFACE_NAME "enp2s0"
#define SER_NAME "/dev/ttyACM0"
#define CHUNKS 27
#define LED_BITS 24  /* LED_CHANNELS*8 */
#define CHUNK_ROWS 8
#define CHUNK_COLS 55
#define LED_INDEX_BYTES 2
#define DATA_BYTES 81  /* CHUNKS*LED_CHANNELS */
#define CHUNK_LEDS 440  /* CHUNK_ROWS*CHUNK_COLS */
#define HEADER_BYTES 14  /* sizeof(struct ether_header) = 6+6+2 */
#define FRAME_BYTES 97  /* HEADER_BYTES+LED_INDEX_BYTES+DATA_BYTES */
#define MAX_BRIGHTNESS 0.05
#define GAME_BRIGHTNESS 0.2

uint8_t frame_buffer[FRAME_BYTES];  /* One Ethernet frame contains data for one LED per chunk  */
uint8_t color_frame[LED_ROWS][LED_COLS][LED_CHANNELS];  /* Colors for full dance floor */
uint8_t color_frame_adj[LED_ROWS][LED_COLS][LED_CHANNELS];  /* Colors with adjusted brightness */
double brightness = 0;

void color_frame_to_eth(uint16_t led_index) {
    /* 
     * Fill frame_buffer with color_frame data at given led_index
     * color_frame format: GRB, GRB, GRB, ... for each row and column of LEDs
     * frame_buffer format: G bit 1, chunk 1; G bit 1, chunk 2; ...; B bit 8,i chunk 27
     */

    uint8_t chunk_led_row = led_index / CHUNK_COLS;
    uint8_t chunk_led_col = led_index % CHUNK_COLS;

    /* led_row and led_col are chunk indices above but with chunk offsets applied */
    uint8_t led_row = 0;
    uint8_t led_col = 0;

    uint8_t i, j, k, l;
    uint16_t frame_buffer_bit_index = 8 * (HEADER_BYTES + LED_INDEX_BYTES);

    memset(frame_buffer + HEADER_BYTES + LED_INDEX_BYTES, 0, DATA_BYTES);

    /* LEDs snake between rows */
    if (chunk_led_row % 2 == 0) {
        chunk_led_col = CHUNK_COLS - chunk_led_col - 1;
    }

    for (i = 0; i < LED_CHANNELS; ++i) {
        /* For each bit of the current channel */
        for (j = 0; j < 8; ++j) {
            /* For each row of chunks */
            for (k = 0; k < 9; ++k) {
                led_row = chunk_led_row + k * CHUNK_ROWS;
                /* For each column of chunks */
                for (l = 0; l < 3; ++l) {
                    led_col = chunk_led_col + l * CHUNK_COLS;

                    /* Select bit j from color_frame, place in chunk_index bit of current_bits */
                    frame_buffer[frame_buffer_bit_index / 8] |= (
                        ((color_frame_adj[led_row][led_col][i] >> (7 - j)) & 1U) <<
                        frame_buffer_bit_index % 8
                    );

                    ++frame_buffer_bit_index;
                }
            }
        }
    }
}

void load_gif_frame(struct frame *frame) {
    /* Copy frame data into color_frame */
    
    uint8_t i, j;
    uint16_t pixel_counter = 0;
    uint8_t ct_index;

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            ct_index = frame->ct_indices[pixel_counter++];
        
            if (!frame->has_transparency || ct_index != frame->transparent_index) {
                /* Transparent pixel retains same color */
                color_frame[i][j][0] = frame->ct[ct_index][1];
                color_frame[i][j][1] = frame->ct[ct_index][0];
                color_frame[i][j][2] = frame->ct[ct_index][2];
            }

            color_frame_adj[i][j][0] = color_frame[i][j][0] * brightness;
            color_frame_adj[i][j][1] = color_frame[i][j][1] * brightness;
            color_frame_adj[i][j][2] = color_frame[i][j][2] * brightness;
        }
    }
}

int prep_gif(struct gif *gif, const char *filename) {
    /* Load GIF and copy first frame data into color_frame */

    uint8_t i, j;
    uint16_t pixel_counter = 0;
    uint8_t ct_index;
    struct frame *frame;
    uint8_t bg_r, bg_g, bg_b;

    if (gif_load(gif, filename) == ERROR_OUT) {
        return ERROR_OUT;
    }

    frame = (struct frame *) dyn_arr_get(&(gif->frames), 0);

    bg_r = frame->ct[gif->bg_index][0];
    bg_g = frame->ct[gif->bg_index][1];
    bg_b = frame->ct[gif->bg_index][2];

    for (i = 0; i < LED_ROWS; ++i) {
        for (j = 0; j < LED_COLS; ++j) {
            ct_index = frame->ct_indices[pixel_counter++];
            if (frame->has_transparency && ct_index == frame->transparent_index) {
                /* Transparent pixel set to bg color */
                color_frame[i][j][0] = bg_g;
                color_frame[i][j][1] = bg_r;
                color_frame[i][j][2] = bg_b;
            }
            else {
                color_frame[i][j][0] = frame->ct[ct_index][1];
                color_frame[i][j][1] = frame->ct[ct_index][0];
                color_frame[i][j][2] = frame->ct[ct_index][2];
            }
            color_frame_adj[i][j][0] = color_frame[i][j][0] * brightness;
            color_frame_adj[i][j][1] = color_frame[i][j][1] * brightness;
            color_frame_adj[i][j][2] = color_frame[i][j][2] * brightness;
        }
    }

    return SUCC_OUT;
}

void print_color_frame() {
    uint8_t i, j;
    uint8_t r, g, b;
    uint32_t formatted_color;

    printf("Frame:\n");
    for (i = 0; i < LED_ROWS; ++i) {
        printf("    ");
        for (j = 0; j < LED_COLS; ++j) {
            g = color_frame[i][j][0];
            r = color_frame[i][j][1];
            b = color_frame[i][j][2];
            formatted_color = (((uint32_t) r) << 16);
            formatted_color |= (((uint32_t) g) << 8);
            formatted_color |= (uint32_t) b;
            printf("0x%X ", formatted_color);
        }
        printf("\n");
    }
}

int get_ser_fd(int *fd) {
    struct termios tty;

    if ((*fd = open(SER_NAME, O_RDONLY | O_NOCTTY | O_SYNC)) < 0) {
        perror("Error [open serial]");
        return ERROR_OUT;
    }

    if (tcgetattr(*fd, &tty) != 0) {
        perror("Error [tcgetattr]");
        return ERROR_OUT;
    }

    cfsetispeed(&tty, B9600);
    
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_iflag &= ~IGNBRK;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_lflag = 0;

    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(*fd, TCSANOW, &tty) != 0) {
        perror("Error [tcsetattr]");
        return ERROR_OUT;
    }

    return SUCC_OUT;
}

void update_brightness(int ser_fd) {
    char rd_char;
    int rd_size = read(ser_fd, &rd_char, 1);
    if (rd_size == 0) {
        return;
    }

    brightness = (uint8_t) rd_char / 255.0 * MAX_BRIGHTNESS;
}

void *ser_thread_func(void *args __attribute__((unused))) {
    int ser_fd;

    if (get_ser_fd(&ser_fd) == ERROR_OUT) {
        brightness = MAX_BRIGHTNESS;
        pthread_exit(0);
    }

    while (1) {
        update_brightness(ser_fd);
    }
}

int main(int argc, char **argv) {
    int socket_fd;
    
    struct ifreq interface_id;
    struct ifreq interface_mac;

    struct ether_header *eth_head = (struct ether_header *) frame_buffer;
    struct sockaddr_ll socket_address;

    uint16_t i;
    uint8_t j, k;

    double millis;
    double prev_millis = 0;

    double last_frame_millis = 0;
    uint16_t frame_index = 0;
    struct frame *current_frame;

    float spf = 0;

    pthread_t ser_thread;
    struct gif gif;

    uint8_t is_game = 1;
    void *game_obj;
    void (*game_init_func)(void *, uint8_t[LED_ROWS][LED_COLS][LED_CHANNELS]);
    void (*game_loop_func)(void *, uint8_t[LED_ROWS][LED_COLS][LED_CHANNELS], struct kb *, float);
    struct kb kb;

    /* Add all game structs here */
    struct game_test game_test;
    struct tetris tetris;

    if (argc < 2) {
        printf("Error: Please provide a GIF filename or game mode\n");
        return ERROR_OUT;
    }

    memset(frame_buffer, 0, FRAME_BYTES);

    if ((socket_fd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
        perror("Error [socket]");
        return ERROR_OUT;
    }

    /* Get interface index from name */
    memset(&interface_id, 0, sizeof(struct ifreq));
    strncpy(interface_id.ifr_name, INTERFACE_NAME, IFNAMSIZ);
    if (ioctl(socket_fd, SIOCGIFINDEX, &interface_id) < 0) {
        perror("Error [SIOCGIFINDEX]");
        return ERROR_OUT;
    }

    /* Get sender MAC address */
    memset(&interface_mac, 0, sizeof(struct ifreq));
    strncpy(interface_mac.ifr_name, INTERFACE_NAME, IFNAMSIZ);
    if (ioctl(socket_fd, SIOCGIFHWADDR, &interface_mac) < 0) {
        perror("Error [SIOCGIFHWADDR]");
        return ERROR_OUT;
    }
    
    /* Construct Ethernet header */
    for (i = 0; i < 6; ++i) {
        eth_head->ether_shost[i] = ((uint8_t *) &interface_mac.ifr_hwaddr.sa_data)[i];

        /* Local MAC address, should match what FPGA is expecting */
        if (i == 0) {
            eth_head->ether_dhost[i] = 0x02;
            socket_address.sll_addr[i] = 0x02;
        }
        else {
            eth_head->ether_dhost[i] = 0x00;
            socket_address.sll_addr[i] = 0x00;
        }
    }
    eth_head->ether_type = htons(ETH_P_IP);

    socket_address.sll_ifindex = interface_id.ifr_ifindex;
    socket_address.sll_halen = ETH_ALEN;

    /* For each game, set game_obj, game_init_func, and game_loop_func if
       the corresponding command line argument is passed */
    if (!strcmp(argv[1], "test")) {
        game_obj = &game_test;
        game_init_func = &game_test_init;
        game_loop_func = &game_test_loop;
    }
    else if (!strcmp(argv[1], "tetris")) {
        game_obj = &tetris;
        game_init_func = &tetris_init;
        game_loop_func = &tetris_loop;
    }
    else {
        /* Not a game, load GIF file */
        is_game = 0;

        /* Control brightness using serial input on separate thread */
        pthread_create(&ser_thread, NULL, ser_thread_func, NULL);
        pthread_detach(ser_thread);

        /* Load GIF file */
        gif_init(&gif);
        if (prep_gif(&gif, argv[1]) == ERROR_OUT) {
            return ERROR_OUT;
        }
        current_frame = (struct frame *) dyn_arr_get(&(gif.frames), 0);
    }

    if (is_game) {
        if (kb_init(&kb) == ERROR_OUT) {
            return ERROR_OUT;
        }
       (*game_init_func)(game_obj, color_frame); 
    }

    #if DO_ETH
        while (1) {
            millis = get_millis();
            spf = (float) (millis - prev_millis) / 1000.0f;
            printf("%f FPS\n", 1.0f / spf);

            if (is_game) {
                kb_update_map(&kb);
                (*game_loop_func)(game_obj, color_frame, &kb, spf);

                /* Limit game brightness */
                for (i = 0; i < LED_ROWS; ++i) {
                    for (j = 0; j < LED_COLS; ++j) {
                        for (k = 0; k < LED_CHANNELS; ++k) {
                            color_frame_adj[i][j][k] = color_frame[i][j][k] * GAME_BRIGHTNESS;
                        }
                    }
                }
            }
            else {
                /* Animate loaded GIF file */
                if (millis - last_frame_millis >= current_frame->delay * 10) {
                    /* Switch to next frame */
                    ++frame_index;
                    if (frame_index == gif.frames.length) {
                        frame_index = 0;
                    }
                    current_frame = (struct frame *) dyn_arr_get(&(gif.frames), frame_index);
                    last_frame_millis = millis;
                    load_gif_frame(current_frame);
                }
            }
     
            /* Send Ethernet packets for each LED */
            for (i = 0; i < CHUNK_LEDS; ++i) {
                /* Set LED index */
                frame_buffer[HEADER_BYTES] = (uint8_t) (i & 0x00ff);
                frame_buffer[HEADER_BYTES + 1] = (uint8_t) (i >> 8);

                /* Set packet data */
                color_frame_to_eth(i);

                /* Send packet */
                if (sendto(
                        socket_fd,
                        frame_buffer,
                        FRAME_BYTES,
                        0,
                        (struct sockaddr *) &socket_address,
                        sizeof(struct sockaddr_ll)
                    ) < 0
                ) {
                    perror("Error [sendto]");
                    return ERROR_OUT;
                }

                usleep(10);
            }

            prev_millis = millis;
        }
    #endif

    if (is_game) {
        kb_free(&kb);
    }
    else {
        gif_free(&gif);
    }
    close(socket_fd);

    return SUCC_OUT;
}

