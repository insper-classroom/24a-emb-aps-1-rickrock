// display.h
// contains constants and function prototypes for lcd.c

#pragma once

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYLEFT 0x02

// flags for display and cursor control
#define LCD_DISPLAYON 0x04
#define LCD_CURSORON 0x02
#define LCD_BLINKON 0x01

// flags for display and cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_MOVERIGHT 0x04

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_2LINE 0x08
#define LCD_5x10DOTS 0x04

// flagsfor backlight control
#define LCD_BACKLIGHT 0x08

#define LCD_ENABLE_BIT 0x04

// by default the LCD display drivers are at 0x27
#define LCD_ADDRESS 0x27

// modes for lcd_send_byte
#define LCD_CHARACTER 1
#define LCD_COMMAND 0

#define MAX_LINES 2
#define MAX_CHARS 16

void i2c_write_byte(uint8_t val);

void lcd_toggle_enable(uint8_t val);

void lcd_send_byte(uint8_t val, uint8_t mode);

void lcd_clear();

void lcd_set_cursor(int line, int position);

static void inline lcd_char(char val);

void lcd_string(const char *s);

void lcd_init();

void lcd_setup();

void lcd_display_welcome();

void lcd_start_page();

void lcd_hs_page();

void lcd_display_hi_scores();

void lcd_playing_sequence(int current_level);

void lcd_your_turn();

void lcd_level_passed(int current_level);

void lcd_game_complete();

void lcd_game_over();

void lcd_show_score(int score);

void lcd_play_again();