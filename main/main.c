/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "config.h"
#include "display.h"
#include "flash.h"
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
volatile bool enter_pressed = false;
volatile bool options_pressed = false;

void btn_callback(uint gpio, uint32_t events) {
    static uint64_t last_press_time = 0;
    uint64_t current_time = time_us_64();

    uint64_t debounce_delay_us = DEBOUNCE_DELAY * 1000;

    if ((current_time - last_press_time) > debounce_delay_us) {
        if (events == GPIO_IRQ_EDGE_FALL) // fall edge
        {
            if (gpio == RED_BUTTON_PIN) {
                red_pressed = true;
            } else if (gpio == BLUE_BUTTON_PIN) {
                blue_pressed = true;
            } else if (gpio == YELLOW_BUTTON_PIN) {
                yellow_pressed = true;
            } else if (gpio == GREEN_BUTTON_PIN) {
                green_pressed = true;
            } else if (gpio == ENTER_BUTTON_PIN) {
                enter_pressed = true;
            } else if (gpio == OPTIONS_BUTTON_PIN) {
                options_pressed = true;
            }
            last_press_time = current_time;
        }
    }
}

int main() {
    stdio_init_all();
    setup_gpio();
    lcd_setup();
    sleep_ms(500);

    gpio_set_irq_enabled_with_callback(RED_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(BLUE_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(YELLOW_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(GREEN_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(ENTER_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    gpio_set_irq_enabled_with_callback(OPTIONS_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    startup();

    app_state current_state = MAIN_MENU;

    while (true) {
        srand(to_us_since_boot(get_absolute_time())); // seed for random number generation

        switch (current_state) {
        case MAIN_MENU: {
            int chosen = show_menu(&enter_pressed, &options_pressed);
            if (chosen == 1) {
                current_state = PLAY_GAME;
            } else if (chosen == 2) {
                current_state = VIEW_HIGH_SCORES;
            }
            break;
        }
        case PLAY_GAME: {
            int current_level = 1;
            generate_sequence();
            while (true) {
                play_sequence(current_level);
                if (!check_sequence(current_level, &red_pressed, &blue_pressed, &yellow_pressed, &green_pressed)) {
                    printf("Game over! You reached level %d\n", current_level);
                    current_state = MAIN_MENU; // go back to the main menu after game over
                    break;
                }
                current_level++;
            }
            break;
        }
        case VIEW_HIGH_SCORES: {
            show_hi_scores(&enter_pressed, &options_pressed);
            current_state = MAIN_MENU;
            break;
        }
        }
    }
}