// config.h
// defines the pins and frequencies used in the game
// it also defines the maximum sequence length

#pragma once

#define RED_LED_PIN 26
#define BLUE_LED_PIN 7
#define YELLOW_LED_PIN 6
#define GREEN_LED_PIN 5

#define RED_BUTTON_PIN 5
#define BLUE_BUTTON_PIN 4
#define YELLOW_BUTTON_PIN 3
#define GREEN_BUTTON_PIN 2

#define BUZZER_PIN 28

#define RED_FREQUENCY 440
#define BLUE_FREQUENCY 330
#define YELLOW_FREQUENCY 277
#define GREEN_FREQUENCY 659

#define MAX_SEQUENCE_LENGTH 15

void setup_gpio();
