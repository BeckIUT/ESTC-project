#ifndef _LED_GPIO_H__
#define _LED_GPIO_H__

#include "nrf_gpio.h"

// LED definitions for PCA10059
// Each LED color is considered a separate LED
#define LEDS_NUMBER    4

#define LED1_G         NRF_GPIO_PIN_MAP(0,6)
#define LED2_R         NRF_GPIO_PIN_MAP(0,8)
#define LED2_G         NRF_GPIO_PIN_MAP(1,9)
#define LED2_B         NRF_GPIO_PIN_MAP(0,12)

#define LED_1          LED1_G
#define LED_2          LED2_R
#define LED_3          LED2_G
#define LED_4          LED2_B

/****
 * @brief: Initialize LED as output pins and button as an input pin
 * @param: no parameters
 * @returns: void
*/
void initialize_board(void);
/***
 * @brief: Write to a LED pin to turn it ON
 * @param: uint32_t integer corresponding LED ID
 * @returns: void
*/
void gpio_led_turn_on(uint32_t led_id);
/***
 * @brief: Write to a LED pin to turn it OFF
 * @param: uint32_t integer corresponding LED ID
 * @returns: void
*/
void gpio_led_turn_off(uint32_t led_id);
/***
 * @brief: Write to a LED pin to turn it ON and then OFF after a pause
 * @param: uint32_t integer corresponding LED ID
 * @returns: void
*/
void gpio_led_toggle(uint32_t led_id);
/***
 * @brief: Check BUTTON PIN if it is pressed
 * @param: no parameters
 * @returns: true if pressed, false otherwise
 * if we read 0 from the pin, then button is pressed. If pin is HIGH, then it is released.
*/
bool gpio_button_is_pressed(void);
/***
 * @brief: Check BUTTON PIN if it is released
 * @param: no parameters
 * @returns: true if released, false otherwise
 * if we read 0 from the pin, then button is pressed. If pin is HIGH, then it is released.
*/
bool gpio_button_is_released(void);
#endif