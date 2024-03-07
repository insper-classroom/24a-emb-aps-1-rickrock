#include "game.h"
#include "config.h"
#include "hardware/gpio.h"
#include "lcd.h"
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
    gpio_put(RED_LED_PIN, 1);
    gpio_put(BLUE_LED_PIN, 1);
    gpio_put(YELLOW_LED_PIN, 1);
    gpio_put(GREEN_LED_PIN, 1);
    play_game_over();
    sleep_ms(2000);
    gpio_put(RED_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 0);
    gpio_put(YELLOW_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
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

void display_sequence(int current_level) {
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
    for (int i = 0; i < current_level; i++) {
        bool inputReceived = false; // flag to indicate when a button press is detected

        // wait for a correct button press according to the sequence
        while (!inputReceived) {
            if (*red_pressed && gamesequence[i] == 0) {
                play_and_light_red();
                *red_pressed = false;
                inputReceived = true;
            } else if (*blue_pressed && gamesequence[i] == 1) {
                play_and_light_blue();
                *blue_pressed = false;
                inputReceived = true;
            } else if (*yellow_pressed && gamesequence[i] == 2) {
                play_and_light_yellow();
                *yellow_pressed = false;
                inputReceived = true;
            } else if (*green_pressed && gamesequence[i] == 3) {
                play_and_light_green();
                *green_pressed = false;
                inputReceived = true;
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
    sleep_ms(2000); // delay before the next level starts
    return true;    // player successfully followed the sequence
}
