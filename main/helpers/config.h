// config.h
// defines the pins and frequencies used in the game
// it also defines the maximum sequence length

#pragma once

#define RED_LED_PIN 13
#define BLUE_LED_PIN 12
#define YELLOW_LED_PIN 10
#define GREEN_LED_PIN 11

#define RED_BUTTON_PIN 9
#define BLUE_BUTTON_PIN 8
#define YELLOW_BUTTON_PIN 6
#define GREEN_BUTTON_PIN 7

#define ENTER_BUTTON_PIN 27
#define OPTIONS_BUTTON_PIN 26

#define BUZZER_PIN 17

#define RED_FREQUENCY 440
#define BLUE_FREQUENCY 330
#define YELLOW_FREQUENCY 277
#define GREEN_FREQUENCY 659
#define GAME_OVER_FREQUENCY 220

#define A4_FREQUENCY 440
#define C4_FREQUENCY 261
#define E4_FREQUENCY 329
#define G4_FREQUENCY 392
#define C5_FREQUENCY 523

#define MAX_SEQUENCE_LENGTH 15

#define DEBOUNCE_DELAY 250

void setup_gpio();
