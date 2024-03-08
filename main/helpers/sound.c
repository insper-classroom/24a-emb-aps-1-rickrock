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

void play_startup_jingle() {
    play_sound(C4_FREQUENCY);
    sleep_ms(250);
    play_sound(E4_FREQUENCY);
    sleep_ms(250);
    play_sound(G4_FREQUENCY);
    sleep_ms(250);
    play_sound(C5_FREQUENCY);
    printf("Playing startup jingle\n");
}

void play_red() {
    play_sound(RED_FREQUENCY);
    printf("Playing red\n");
}

void play_blue() {
    play_sound(BLUE_FREQUENCY);
    printf("Playing blue\n");
}

void play_yellow() {
    play_sound(YELLOW_FREQUENCY);
    printf("Playing yellow\n");
}

void play_green() {
    play_sound(GREEN_FREQUENCY);
    printf("Playing green\n");
}

void play_game_over() {
    play_sound(A4_FREQUENCY);
    sleep_ms(300);
    play_sound(E4_FREQUENCY);
    sleep_ms(300);
    play_sound(C4_FREQUENCY);
    printf("Playing game over sound\n");
}
