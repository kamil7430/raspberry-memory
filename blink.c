#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
// #include <periphery/gpio.h>

#include "includes/gpio.h"

int main(void) {
    const int NUM_GPIOS = 8;

    const int PINS[] ={
        // diodes
        12, 13, 14, 15,
        // buttons
        16, 17, 18, 19,
    };

    const char *FILE_PATH = "/dev/gpiochip0";

    gpio_t *gpios[] = {
        // diodes
        gpio_new(), gpio_new(), gpio_new(), gpio_new(), 
        // buttons
        gpio_new(), gpio_new(), gpio_new(), gpio_new(), 
    };

    // Open gpios
    for (int i = 0; i < NUM_GPIOS / 2; i++) {
        if (gpio_open(gpios[i], FILE_PATH, PINS[i], GPIO_DIR_OUT_LOW) < 0) {
            fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
        if (gpio_open(gpios[i + NUM_GPIOS / 2], FILE_PATH, PINS[i + NUM_GPIOS / 2], GPIO_DIR_IN) < 0) {
            fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(gpios[i + NUM_GPIOS / 2]));
            exit(1);
        }
    }

    // Set debounce period
    const uint32_t debounce_us = 20000;
    for (int i = 0; i < NUM_GPIOS; i++) {
        if (gpio_set_debounce_us(gpios[i], debounce_us) < 0) {
            fprintf(stderr, "gpio_set_debounce_us(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
    }

    // Set edge for buttons
    for (int i = NUM_GPIOS / 2 - 1; i < NUM_GPIOS; i++) {
        if (gpio_set_edge(gpios[i], GPIO_EDGE_RISING) < 0) {
            fprintf(stderr, "gpio_set_edge(): %s\n", gpio_errmsg(gpios[i]));
            exit(1);
        }
    }

    // Close gpios
    for (int i = 0; i < NUM_GPIOS; i++) {
        gpio_close(gpios[i]);
        gpio_free(gpios[i]);
    }

    return 0;
}
//    for (int i = 0; i < 5; i++) {
//        /* Write output GPIO with !value */
//        if (gpio_write(gpio_out, true) < 0) {
//            fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(gpio_out));
//            exit(1);
//        }
//        sleep(2);
//
//        if (gpio_write(gpio_out, false) < 0) {
//            fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(gpio_out));
//            exit(1);
//        }
//        sleep(2);
//    }
//
//    gpio_close(gpio_out);
//    gpio_free(gpio_out);
