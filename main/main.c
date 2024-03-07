/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "config.h"
#include "display.h"
#include "game.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "sound.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

volatile bool red_pressed = false;
volatile bool blue_pressed = false;
volatile bool yellow_pressed = false;
volatile bool green_pressed = false;

void btn_callback(uint gpio, uint32_t events) {
    static uint64_t last_press_time = 0;
    uint64_t current_time = time_us_64();

    uint64_t debounce_delay_us = DEBOUNCE_DELAY * 1000;

    if ((current_time - last_press_time) > debounce_delay_us) {
        if (events == GPIO_IRQ_EDGE_FALL) // fall edge
        {
            if (gpio == RED_BUTTON_PIN) {
                red_pressed = true;
                printf("Red pressed\n");
            } else if (gpio == BLUE_BUTTON_PIN) {
                blue_pressed = true;
                printf("Blue pressed\n");
            } else if (gpio == YELLOW_BUTTON_PIN) {
                yellow_pressed = true;
                printf("Yellow pressed\n");
            } else if (gpio == GREEN_BUTTON_PIN) {
                green_pressed = true;
                printf("Green pressed\n");
            }
            last_press_time = current_time;
        }
    }
}

int main() {
    stdio_init_all();
    setup_gpio();

    gpio_set_irq_enabled_with_callback(RED_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BLUE_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(YELLOW_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(GREEN_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    while (true) {
        srand(to_us_since_boot(get_absolute_time()));
        int current_level = 1;
        generate_sequence();
        while (true) {
            play_sequence(current_level);
            if (!check_sequence(current_level, &red_pressed, &blue_pressed, &yellow_pressed, &green_pressed)) {
                printf("Game over! You reached level %d\n", current_level);
                break;
            }
            current_level++;
        }
    }
}