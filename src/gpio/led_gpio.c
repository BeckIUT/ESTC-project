#include "led_gpio.h"
#include "../utils/delay.h"

/**
 * Output PIN is configured NO PULL resistor
 * Hence its STATE is ACTIVE LOW
*/
#define LED_ON         0
#define LED_OFF        1
// There is only one button for the application
// as the second button is used for a RESET.
#define BUTTONS_NUMBER 1

#define BUTTON_1       NRF_GPIO_PIN_MAP(1,6)
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP


void initialize_board(void)
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

void gpio_led_toggle(uint32_t led_id)
{
    gpio_led_turn_on(led_id);
    delay_with_pwm_button(PAUSE_MS, led_id); // send T_ON time here
    // delay_with_button_check(PAUSE_MS);
    gpio_led_turn_off(led_id);
}

bool gpio_button_is_pressed(void)
{
    return nrf_gpio_pin_read(BUTTON_1) == 0; // LOW pin indicates button is pressed
}

bool gpio_button_is_released(void)
{
    return nrf_gpio_pin_read(BUTTON_1) > 0; // HIGH pin indicates button is released
}