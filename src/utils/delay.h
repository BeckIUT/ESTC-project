#ifndef _DELAY_H__
#define _DELAY_H__

#include "nrf_delay.h"

#define PAUSE_MS 100
#define RELEASE_CHECK_INTERVAL_MS 10
#define MILLISECOND 1
/***
 * @brief This function is a custom delay function
 * @details Function checks if BUTTON is released every millisecond,
 *  if released delay function will buy time until BUTTON is pressed again
 * @param: uint32_t delay time in milliseconds
 * @returns: void
*/
void delay_with_button_check(uint32_t ms_time);
#endif