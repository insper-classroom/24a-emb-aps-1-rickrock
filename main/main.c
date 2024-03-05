/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "config.h"
#include "game.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "sound.h"
#include <stdio.h>
#include <time.h>

volatile bool red_pressed = false;
volatile bool blue_pressed = false;
volatile bool yellow_pressed = false;
volatile bool green_pressed = false;

void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x04) // fall edge
    {
        if (gpio == RED_BUTTON_PIN) {
            red_pressed = true;
        } else if (gpio == BLUE_BUTTON_PIN) {
            blue_pressed = true;
        } else if (gpio == YELLOW_BUTTON_PIN) {
            yellow_pressed = true;
        } else {
            green_pressed = true;
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
        int current_level = 1;
        while (true) {
            generate_sequence(current_level);
            display_sequence(current_level);
            if (!check_sequence(current_level, red_pressed, blue_pressed, yellow_pressed, green_pressed)) {
                printf("Game over! You reached level %d\n", current_level);
                break;
            }
            current_level++;
        }
    }
}