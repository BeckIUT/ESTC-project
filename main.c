#include <stdbool.h>
#include <stdint.h>
#include "src/gpio/led_gpio.h"
#include "src/utils/delay.h"

#define SEQUENCE { 0, 1, 2, 3 } // LRGB

void blinkLEDs()
{
    uint8_t sequence[] = SEQUENCE;
    uint8_t counter = 0;
    while(gpio_button_is_pressed()){
        for(; counter < NRFX_ARRAY_SIZE(sequence); counter++){
            switch(sequence[counter]){
                case 0:
                    gpio_led_turn_on(LED_1);
                    delay_with_button_check(PAUSE_MS);
                    gpio_led_turn_off(LED_1);
                    break;
                case 1:
                    gpio_led_turn_on(LED_2);
                    delay_with_button_check(PAUSE_MS);
                    gpio_led_turn_off(LED_2);
                    break;
                case 2:
                    gpio_led_turn_on(LED_3);
                    delay_with_button_check(PAUSE_MS);
                    gpio_led_turn_off(LED_3);
                    break;
                case 3:
                    gpio_led_turn_on(LED_4);
                    delay_with_button_check(PAUSE_MS);
                    gpio_led_turn_off(LED_4);
                    break;
                default:
                    break;
            }
            while(gpio_button_is_released())
                nrf_delay_ms(RELEASE_CHECK_INTERVAL);
        }
        counter = counter % NRFX_ARRAY_SIZE(sequence);
    }
    
}

int main(void)
{
    /* Configure board. */
    initialize_board();

    /* Toggle LEDs. */
    while (true)
    {
        blinkLEDs();
    }
}