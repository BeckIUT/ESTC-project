#include "led_gpio.h"

void initialize_board()
{
    nrf_gpio_cfg_output(LED_1); // LED_1 Green
    gpio_led_turn_off(LED_1);
    nrf_gpio_cfg_output(LED_2); // LED_2 Red
    gpio_led_turn_off(LED_2);
    nrf_gpio_cfg_output(LED_3); // LED_3 Green
    gpio_led_turn_off(LED_3);
    nrf_gpio_cfg_output(LED_4); // LED_4 Blue
    gpio_led_turn_off(LED_4);
    nrf_gpio_cfg_input(BUTTON_1, BUTTON_PULL); // PULLUP
}

void gpio_led_turn_on(uint32_t led_id)
{
    nrf_gpio_pin_write(led_id, LED_ON); // LOW pin value => LED is ON, , ACTIVE LOW
}

void gpio_led_turn_off(uint32_t led_id)
{
    nrf_gpio_pin_write(led_id, LED_OFF); // HIGH pin value => LED is OFF, ACTIVE LOW
}

bool gpio_button_is_pressed()
{
    // LOW pin indicates button is pressed
    return nrf_gpio_pin_read(BUTTON_1) == 0;
}

bool gpio_button_is_released()
{
    return nrf_gpio_pin_read(BUTTON_1) > 0; // HIGH pin indicates button is released
}