#include "delay.h"
#include "../gpio/led_gpio.h"
#include "../pwm/pwm.h"

void delay_with_button_check(uint32_t ms_time)
{
   while(ms_time > 0){
        while(gpio_button_is_released())
            nrf_delay_ms(MILLISECOND); // wait untill pressed again
        nrf_delay_ms(MILLISECOND); // LED pause
        ms_time -= MILLISECOND;
   } 
}

void delay_with_pwm_button(uint32_t ms_time, uint32_t led_id)
{
    static uint32_t t_on = DUTY_MIN;
    static uint32_t t_off = DUTY_MAX;
    static uint8_t duty_cycle_direction = 0; // 0 is increasing, 1 decreasing
    while(ms_time > 0){
        while(gpio_button_is_released())
            nrf_delay_ms(MILLISECOND); // wait untill pressed again
        nrf_delay_us(t_on);
        gpio_led_turn_off(led_id);
        nrf_delay_us(t_off);
        gpio_led_turn_on(led_id);
        if(duty_cycle_direction == 0){
            t_on = t_on + DUTY_CYCLE_STEP;
            t_off = DUTY_MAX - t_on;
            if(t_on >= DUTY_MAX)
                duty_cycle_direction = 1;
        }else if (duty_cycle_direction == 1){
            t_on = t_on - DUTY_CYCLE_STEP;
            t_off = DUTY_MAX - t_on;
            if(t_on <= DUTY_MIN)
                duty_cycle_direction = 0;
        }
        ms_time -= MILLISECOND; // decrement operation depends on PERIOD
    }
}