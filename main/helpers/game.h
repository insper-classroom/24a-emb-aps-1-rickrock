// game.h
// contains functions that generate and control the game

#pragma once

#include "config.h"
#include "display.h"
#include "sound.h"
#include <stdbool.h>

extern int gamesequence[MAX_SEQUENCE_LENGTH];

void play_and_light_red();

void play_and_light_blue();

void play_and_light_yellow();

void play_and_light_green();

void play_and_light_game_over();

void play_and_light_win();

void startup();

int show_menu(volatile bool *select_pressed, volatile bool *start_pressed);

void show_hi_scores(volatile bool *enter_pressed, volatile bool *options_pressed);

void generate_sequence();

void play_sequence(int current_level);

bool check_sequence(int current_level, volatile bool *red_pressed, volatile bool *blue_pressed, volatile bool *yellow_pressed, volatile bool *green_pressed);