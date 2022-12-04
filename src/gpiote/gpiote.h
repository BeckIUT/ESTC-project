#ifndef GPIOTE_H__
#define GPIOTE_H__

#include "nrfx_gpiote.h"
#include "app_timer.h"

volatile bool double_click_toggle_flag; // create separate flag for PWM,
// and use main.c to communicate flags between modules
// main.c get gpiote flag --> set pwm flag
/**
 * @brief GPIOTE function to initialize Tasks & Events
 * Uses BUTTON pin as GPIO IN
 * @param void
 * @returns: void
*/
void gpiote_init(void);
/**
 * @brief Timer initialization function
*/
void timer_init(void);
/**
 * @brief Debouncing timer expiration handler
*/
void debounce_timer_handler(void * p_context);
/**
 * @brief Double click check timer expiration handler
*/
void double_click_timer_handler(void * p_context);
/**
 * @brief Each button PIN toggle handler
*/
void button_toggle_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
#endif