// lcd.h
// contains definitions and declarations for the lcd display

#pragma once

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define LCD_ADDR 0x27

void lcd_init();

void lcd_send_command(uint8_t command);

void lcd_display_string(const char *str);

void lcd_clear();