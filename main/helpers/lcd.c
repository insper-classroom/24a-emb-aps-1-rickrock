#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void lcd_init(uint8_t addr) {
    i2c_init(I2C_PORT, 100000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void lcd_send_command(uint8_t command) {
    uint8_t data[2];
    data[0] = 0x80;
    data[1] = command;
    i2c_write_blocking(I2C_PORT, 0x3E, data, 2, false);
}

void lcd_display_string(const char *str) {
    while (*str) {
        uint8_t data[2] = {0x40, *str++};
        i2c_write_blocking(I2C_PORT, 0x3E, data, 2, false);
    }
}

void lcd_clear() {
    lcd_send_command(0x01);
    sleep_ms(2);
}