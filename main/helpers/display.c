#include "display.h"
#include "flash.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

void i2c_write_byte(uint8_t val) {
    i2c_write_blocking(i2c_default, LCD_ADDRESS, &val, 1, false);
}

void lcd_toggle_enable(uint8_t val) {
    sleep_ms(0.6);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_ms(0.6);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_ms(0.6);
}

void lcd_send_byte(uint8_t val, uint8_t mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear() {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
    sleep_ms(2);
}

void lcd_set_cursor(int line, int position) {
    int val = (line == 0) ? (0x80 + position) : (0xC0 + position);
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init() {
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

void lcd_setup() {
    i2c_init(i2c_default, 100000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    lcd_init();
}

void lcd_display_welcome() {
    lcd_clear();
    lcd_string("APS 1");
    lcd_set_cursor(1, 0);
    lcd_string("Genius 2.0");
    sleep_ms(3000);
    lcd_clear();
    lcd_string("ENT p/ sim");
    lcd_set_cursor(1, 0);
    lcd_string("OPT p/ mudar");
}

void lcd_start_page() {
    lcd_clear();
    lcd_string("Iniciar jogo?");
    lcd_set_cursor(1, 0);
    lcd_string("ENT p/ sim");
}

void lcd_hs_page() {
    lcd_clear();
    lcd_string("Hi-Scores");
    lcd_set_cursor(1, 0);
    lcd_string("ENT p/ ver");
}

void lcd_playing_sequence(int current_level) {
    lcd_clear();
    char level[16];
    sprintf(level, "Nivel: %d", current_level);
    lcd_string(level);
    lcd_set_cursor(1, 0);
    lcd_string("Tocando...");
}

void lcd_your_turn() {
    lcd_clear();
    lcd_string("Sua vez!");
}

void lcd_level_passed(int current_level) {
    lcd_clear();
    char level[16];
    sprintf(level, "Nivel %d", current_level);
    lcd_string(level);
    lcd_set_cursor(1, 0);
    lcd_string("Passou!");
}

void lcd_game_complete() {
    lcd_clear();
    lcd_string("Parabens!");
    lcd_set_cursor(1, 0);
    lcd_string("Voce venceu!");
}

void lcd_game_over() {
    lcd_clear();
    lcd_string("Game Over!");
    lcd_set_cursor(1, 0);
    lcd_string("Voce errou!");
}

void lcd_show_score(int score) {
    lcd_clear();
    char level[16];
    sprintf(level, "Pontuacao: %d", score - 1);
    lcd_string(level);
    lcd_set_cursor(1, 0);
}

void lcd_play_again() {
    lcd_string("De novo?");
    lcd_set_cursor(1, 0);
    lcd_string("1. Sim  2. Nao");
}