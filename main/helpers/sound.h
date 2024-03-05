// sound.h
// contains functions to play sounds on the buzzer

#pragma once

#include "config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

void play_sound(int frequency);

void play_red();

void play_blue();

void play_yellow();

void play_green();