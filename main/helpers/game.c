#include "game.h"
#include "config.h"
#include "display.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "sound.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gamesequence[MAX_SEQUENCE_LENGTH];

void play_and_light_red() {
    gpio_put(RED_LED_PIN, 1);
    play_red();
    sleep_ms(500);
    gpio_put(RED_LED_PIN, 0);
    sleep_ms(500);
}

void play_and_light_blue() {
    gpio_put(BLUE_LED_PIN, 1);
    play_blue();
    sleep_ms(500);
    gpio_put(BLUE_LED_PIN, 0);
    sleep_ms(500);
}

void play_and_light_yellow() {
    gpio_put(YELLOW_LED_PIN, 1);
    play_yellow();
    sleep_ms(500);
    gpio_put(YELLOW_LED_PIN, 0);
    sleep_ms(500);
}

void play_and_light_green() {
    gpio_put(GREEN_LED_PIN, 1);
    play_green();
    sleep_ms(500);
    gpio_put(GREEN_LED_PIN, 0);
    sleep_ms(500);
}

void play_and_light_game_over() {
    play_game_over();
    for (int i = 0; i < 3; i++) {
        gpio_put(RED_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(RED_LED_PIN, 0);
    }
}

void show_welcome() {
    lcd_display_welcome();
    sleep_ms(2000);
}

int show_menu(volatile bool *select_pressed, volatile bool *start_pressed) {
    bool on_start_page = true;

    while (true) {
        if (on_start_page) {
            lcd_start_page();
        } else {
            lcd_hs_page();
        }

        if (*select_pressed) {
            on_start_page = !on_start_page;
            *select_pressed = false;
        }

        if (*start_pressed) {
            *start_pressed = false;
            return on_start_page ? 1 : 2;
        }
    }
}

int show_hi_scores(volatile bool *select_pressed, volatile bool *start_pressed) {
    lcd_display_hi_scores();
    while (true) {
        if (*select_pressed) {
            *select_pressed = false;
            return show_menu(select_pressed, start_pressed);
        }
    }
}

void generate_sequence() {
    for (int i = 0; i < MAX_SEQUENCE_LENGTH; i++) {
        gamesequence[i] = rand() % 4; // 0 for red, 1 for blue, 2 for yellow, 3 for green
    }
    printf("Generated sequence: ");
    for (int i = 0; i < MAX_SEQUENCE_LENGTH; i++) {
        printf("%d ", gamesequence[i]);
    }
}

void play_sequence(int current_level) {
    lcd_playing_sequence(current_level);
    printf("Current level: %d\n", current_level);
    for (int i = 0; i < current_level; i++) {
        if (gamesequence[i] == 0) {
            play_and_light_red();
        } else if (gamesequence[i] == 1) {
            play_and_light_blue();
        } else if (gamesequence[i] == 2) {
            play_and_light_yellow();
        } else {
            play_and_light_green();
        }
    }
}

bool check_sequence(int current_level, volatile bool *red_pressed, volatile bool *blue_pressed, volatile bool *yellow_pressed, volatile bool *green_pressed) {
    lcd_your_turn();
    for (int i = 0; i < current_level; i++) {
        bool input_received = false; // flag to indicate when a button press is detected

        // wait for a correct button press according to the sequence
        while (!input_received) {
            if (*red_pressed && gamesequence[i] == 0) {
                play_and_light_red();
                *red_pressed = false;
                input_received = true;
            } else if (*blue_pressed && gamesequence[i] == 1) {
                play_and_light_blue();
                *blue_pressed = false;
                input_received = true;
            } else if (*yellow_pressed && gamesequence[i] == 2) {
                play_and_light_yellow();
                *yellow_pressed = false;
                input_received = true;
            } else if (*green_pressed && gamesequence[i] == 3) {
                play_and_light_green();
                *green_pressed = false;
                input_received = true;
            } else if (*red_pressed || *blue_pressed || *yellow_pressed || *green_pressed) {
                play_and_light_game_over();
                *red_pressed = false;
                *blue_pressed = false;
                *yellow_pressed = false;
                *green_pressed = false;
                sleep_ms(2000);
                return false; // incorrect input, end the game
            }
            sleep_ms(10); // small delay to allow CPU to perform other tasks
        }
    }
    printf("Level passed!\n");
    lcd_level_passed(current_level);
    sleep_ms(1000); // delay before the next level starts
    return true;    // player successfully followed the sequence
}
