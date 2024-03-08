// flash.h
// definitions and declarations for the flash module

#pragma once

#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

#define FLASH_SECTOR_SIZE 4096
#define FLASH_OFFSET (32 * 1024)
#define MAX_HIGH_SCORES 5
#define HIGH_SCORE_MARKER 0x12345678

typedef struct {
    int score;
} high_score;

typedef struct {
    uint32_t marker;
    high_score scores[MAX_HIGH_SCORES];
} high_scores_data;

bool check_and_init_high_scores(high_scores_data *data);
bool load_high_scores(high_score *highscores);
bool save_high_scores(high_scores_data *data);
void update_high_score(high_score *highscores, int new_score);