#include "pwm.h"
#include "../gpio/led_gpio.h"
#include "../gpiote/gpiote.h"

static uint32_t t_on = DUTY_MIN;
static uint32_t t_off = DUTY_MAX;
static uint8_t duty_cycle_direction = 0; // 0 is increasing, 1 decreasing
volatile bool pwm_cycle_end = false;

void delay_with_pwm(uint32_t led_id)
{
    pwm_cycle_end = false;
    while(!pwm_cycle_end){
        nrf_delay_us(t_on);
        gpio_led_turn_off(led_id);
        nrf_delay_us(t_off);
        gpio_led_turn_on(led_id);
        update_pwm();
    }
}

void update_pwm()
{
    if(double_click_toggle_flag){
        if(duty_cycle_direction == 0){
            t_on = t_on + DUTY_CYCLE_STEP;
            t_off = DUTY_MAX - t_on;
            if(t_on >= DUTY_MAX)
                duty_cycle_direction = 1;
        }else if (duty_cycle_direction == 1){
            t_on = t_on - DUTY_CYCLE_STEP;
            t_off = DUTY_MAX - t_on;
            if(t_on <= DUTY_MIN){
                duty_cycle_direction = 0;
                pwm_cycle_end = true;
            }
        }
    }
}