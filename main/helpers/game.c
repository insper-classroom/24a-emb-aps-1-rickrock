#include "game.h"
#include "config.h"
#include "display.h"
#include "flash.h"
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
    lcd_game_over();
    play_game_over();
    for (int i = 0; i < 3; i++) {
        gpio_put(RED_LED_PIN, 1);
        sleep_ms(100);
        gpio_put(RED_LED_PIN, 0);
        sleep_ms(100);
    }
}

void startup() {
    play_startup_jingle();
    lcd_display_welcome();
    sleep_ms(3000);
}

int show_menu(volatile bool *enter_pressed, volatile bool *options_pressed) {
    bool on_start_page = true;
    bool update_display = true;

    while (true) {
        if (update_display) {
            if (on_start_page) {
                lcd_start_page();
            } else {
                lcd_hs_page();
            }
            update_display = false;
        }

        if (*options_pressed) {
            on_start_page = !on_start_page;
            *options_pressed = false;
            update_display = true;
        }

        if (*enter_pressed) {
            *enter_pressed = false;
            return on_start_page ? 1 : 2;
        }
    }
}

void show_hi_scores(volatile bool *enter_pressed, volatile bool *options_pressed) {
    high_scores_data highscores;
    if (!check_and_init_high_scores(&highscores)) {
        lcd_clear();
        lcd_string("Sem scores!"); // no scores initialized
        sleep_ms(2000);
        return;
    }

    int current_score_index = 0;
    while (!*enter_pressed && !*options_pressed) {
        lcd_clear();
        lcd_string("Top ");
        char score_index_str[2]; // string to hold '1', '2', etc.
        sprintf(score_index_str, "%d", current_score_index + 1);
        lcd_string(score_index_str);

        lcd_set_cursor(1, 0);
        if (highscores.scores[current_score_index].score == -1) {
            lcd_string("N/A"); // display N/A for uninitialized scores
        } else {
            char score_str[16];
            sprintf(score_str, "%d", highscores.scores[current_score_index].score);
            lcd_string(score_str);
        }

        sleep_ms(3000); // display each score for 3 seconds

        current_score_index = (current_score_index + 1) % MAX_HIGH_SCORES;
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
    printf("Current level: %d\n", current_level);
    lcd_playing_sequence(current_level);
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
    sleep_ms(500);
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
                lcd_show_score(current_level);
                sleep_ms(3000);

                high_scores_data highscores;
                if (check_and_init_high_scores(&highscores)) {
                    update_high_score(highscores.scores, current_level - 1);
                    save_high_scores(&highscores);
                }

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
