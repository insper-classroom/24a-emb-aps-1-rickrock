#include "game.h"
#include "config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "sound.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gamesequence[MAX_SEQUENCE_LENGTH];

void generate_sequence(int current_level) {
    srand(time(NULL));
    for (int i = 0; i < current_level; i++) {
        gamesequence[i] = rand() % 4; // 0 for red, 1 for blue, 2 for yellow, 3 for green
    }
}

void display_sequence(int current_level) {
    for (int i = 0; i < current_level; i++) {
        if (gamesequence[i] == 0) {
            gpio_put(RED_LED_PIN, 1);
            play_red();
            sleep_ms(500);
            gpio_put(RED_LED_PIN, 0);
            sleep_ms(500);
        } else if (gamesequence[i] == 1) {
            gpio_put(BLUE_LED_PIN, 1);
            play_blue();
            sleep_ms(500);
            gpio_put(BLUE_LED_PIN, 0);
            sleep_ms(500);
        } else if (gamesequence[i] == 2) {
            gpio_put(YELLOW_LED_PIN, 1);
            play_yellow();
            sleep_ms(500);
            gpio_put(YELLOW_LED_PIN, 0);
            sleep_ms(500);
        } else {
            gpio_put(GREEN_LED_PIN, 1);
            play_green();
            sleep_ms(500);
            gpio_put(GREEN_LED_PIN, 0);
            sleep_ms(500);
        }
    }
}

bool check_sequence(int current_level, bool red_pressed, bool blue_pressed, bool yellow_pressed, bool green_pressed) {
    for (int i = 0; i < current_level; i++) {
        while (1) {
            if (red_pressed && gamesequence[i] == 0) {
                break;
            } else if (blue_pressed && gamesequence[i] == 1) {
                break;
            } else if (yellow_pressed && gamesequence[i] == 2) {
                break;
            } else if (green_pressed && gamesequence[i] == 3) {
                break;
            }
        }
    }
    return true;
}