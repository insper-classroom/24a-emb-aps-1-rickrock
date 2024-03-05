// game.h
// contains functions that generate and control the game

#pragma once

#include "config.h"
#include <stdbool.h>

extern int gamesequence[MAX_SEQUENCE_LENGTH];

void generate_sequence(int current_level);

void display_sequence(int current_level);

bool check_sequence(int current_level, bool red_pressed, bool blue_pressed, bool yellow_pressed, bool green_pressed);