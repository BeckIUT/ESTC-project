#ifndef PWM_H_
#define PWM_H_

#include "nrf_delay.h"

/***
 * @brief This function is a custom delay function
 * @details Function runs full PWM cycle 0 -> 100 -> 0
 * @param uint32_t currect LED
 * @returns: void
*/
void delay_with_pwm(uint32_t led_id);
/***
 * @brief This function is a custom pwm update function
 * @details Function runs when user double clicks the BUTTON, and updates the duty cycle one step every function call
 * @param void
 * @returns: void
*/
void update_pwm();
#endif