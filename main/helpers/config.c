#include "config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

void setup_gpio() {
    gpio_init(RED_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_init(YELLOW_LED_PIN);
    gpio_init(GREEN_LED_PIN);

    gpio_init(RED_BUTTON_PIN);
    gpio_init(BLUE_BUTTON_PIN);
    gpio_init(YELLOW_BUTTON_PIN);
    gpio_init(GREEN_BUTTON_PIN);

    gpio_init(BUZZER_PIN);

    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_set_dir(RED_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(BLUE_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(YELLOW_BUTTON_PIN, GPIO_IN);
    gpio_set_dir(GREEN_BUTTON_PIN, GPIO_IN);

    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}