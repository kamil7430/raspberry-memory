#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <periphery/gpio.h>

// #include "includes/gpio.h"

int main(void) {
    const int DIODES = 4;
    const int BUTTONS = 4;
    const int NUM_GPIOS = DIODES + BUTTONS;

    const int PINS[] ={
        // diodes
        12, 13, 14, 15,
        // buttons
        16, 17, 18, 19,
    };

    const char *FILE_PATH = "/dev/gpiochip0";

    const int GAME_LENGTH = 5;
    const int SECONDS_TO_MEMORIZE = 1;

    gpio_t *gpios[] = {
        // diodes
        gpio_new(), gpio_new(), gpio_new(), gpio_new(), 
        // buttons
        gpio_new(), gpio_new(), gpio_new(), gpio_new(), 
    };

    puts("Opening the gpios...");
    for (int i = 0; i < DIODES; i++) {
        if (gpio_open(gpios[i], FILE_PATH, PINS[i], GPIO_DIR_OUT_LOW) < 0) {
            fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
    }
    for (int i = DIODES - 1; i < NUM_GPIOS; i++) {
        if (gpio_open(gpios[i], FILE_PATH, PINS[i], GPIO_DIR_IN) < 0) {
            fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
    }

    puts("Setting edges for buttons...");
    for (int i = DIODES - 1; i < NUM_GPIOS; i++) {
        if (gpio_set_edge(gpios[i], GPIO_EDGE_RISING) < 0) {
            fprintf(stderr, "gpio_set_edge(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
    }

    puts("Initializing the game...");
    int sequence[GAME_LENGTH];
    for (int i = 0; i < GAME_LENGTH; i++) {
        sequence[i] = rand() % BUTTONS;
    }

    puts("Sequence showing phase starts!");
    puts("Observe the diodes!");
    for (int i = 0; i < GAME_LENGTH; i++) {
        if (gpio_write(gpios[sequence[i]], true) < 0) {
            fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(gpios[sequence[i]]));
            exit(1);
        }
        sleep(SECONDS_TO_MEMORIZE);
        if (gpio_write(gpios[sequence[i]], false) < 0) {
            fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(gpios[sequence[i]]));
            exit(1);
        }
        sleep(SECONDS_TO_MEMORIZE);
    }

    puts("Sequence guessing phase starts!");
    bool poll_states[BUTTONS] = {};
    int seq_idx = 0;
    puts("Make your first choice now!");
    while (true) {
        if (gpio_poll_multiple(gpios + DIODES, BUTTONS, -1, poll_states) < 0) {
            fprintf(stderr, "gpio_poll_multiple() error\n");
            break;
        }

        // Sleep for 20ms since the kernel does not support debounce
        usleep(20000);

        int clicked_idx = -1;
        for (int i = 0; i < BUTTONS; i++) {
            if (poll_states[i]) {
                bool level;
                gpio_read(gpios[i], &level);
                if (!level) {
                    clicked_idx = i;
                }
            }
        }

        if (clicked_idx >= 0) {
            printf("Button %d clicked!\n", clicked_idx + 1);
            if (sequence[seq_idx] == clicked_idx) {
                puts("That is correct!");
                seq_idx++;
                if (seq_idx == GAME_LENGTH) {
                    puts("Congratulations! You won!");
                    break;
                }
                sleep(1);
                printf("Make your %d choice now!", seq_idx + 1);
            } else {
                puts("Unfortunately, this is incorrect choice :(\nYou lost!");
                break;
            }
        }
    }

    puts("Cleaning up the gpios...");
    for (int i = 0; i < NUM_GPIOS; i++) {
        gpio_close(gpios[i]);
        gpio_free(gpios[i]);
    }

    puts("Closing... Goodbye!");
    return 0;
}