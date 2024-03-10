#include "hardware/flash.h"
#include "flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

bool check_and_init_high_scores(high_scores_data *data) {
    const high_scores_data *flash_data = (const high_scores_data *)(XIP_BASE + FLASH_OFFSET);
    if (flash_data->marker != HIGH_SCORE_MARKER) {
        // initialize high scores and marker
        for (int i = 0; i < MAX_HIGH_SCORES; i++) {
            data->scores[i].score = -1; // default value indicating no score
        }
        data->marker = HIGH_SCORE_MARKER;

        // save the initialized data to flash
        save_high_scores(data);
        return false; // indicates data was not initially valid and was reset
    }

    memcpy(data, flash_data, sizeof(high_scores_data));
    return true; // indicates existing valid data was loaded
}

bool load_high_scores(high_score *highscores) {
    const uint8_t *flash_source = (const uint8_t *)(XIP_BASE + FLASH_OFFSET);
    memcpy(highscores, flash_source, sizeof(high_score) * MAX_HIGH_SCORES);

    return true;
}

bool save_high_scores(high_scores_data *data) {
    uint8_t buffer[FLASH_SECTOR_SIZE] = {0};
    memcpy(buffer, data, sizeof(high_scores_data));
    flash_range_erase(FLASH_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_OFFSET, buffer, sizeof(high_scores_data));
    return true;
}

void update_high_score(high_score *highscores, int new_score) {
    for (int i = 0; i < MAX_HIGH_SCORES; i++) {
        if (new_score > highscores[i].score) {
            for (int j = MAX_HIGH_SCORES - 1; j > i; j--) {
                highscores[j] = highscores[j - 1];
            }
            highscores[i].score = new_score;
            break;
        }
    }
}