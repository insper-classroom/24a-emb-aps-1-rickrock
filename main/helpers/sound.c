#include "sound.h"
#include "config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

void play_sound(int frequency) {
    int interval = 1000000 / frequency;
    int num_intervals = 300 * 1000 / interval;
    for (int i = 0; i < num_intervals; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(interval / 2);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(interval / 2);
    }
}

void play_red() {
    play_sound(RED_FREQUENCY);
}

void play_blue() {
    play_sound(BLUE_FREQUENCY);
}

void play_yellow() {
    play_sound(YELLOW_FREQUENCY);
}

void play_green() {
    play_sound(GREEN_FREQUENCY);
}