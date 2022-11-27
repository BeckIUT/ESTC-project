#include "delay.h"
#include "../gpio/led_gpio.h"

void delay_with_button_check(uint32_t ms_time)
{
   while(ms_time > 0){
        while(gpio_button_is_released())
            nrf_delay_ms(MILLISECOND); // wait untill pressed again
        nrf_delay_ms(MILLISECOND); // LED pause
        ms_time -= MILLISECOND;
   } 
}

