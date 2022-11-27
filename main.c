#include <stdbool.h>
#include <stdint.h>
#include "src/gpio/led_gpio.h"
#include "src/pwm/pwm.h"
#include "src/utils/delay.h"
#include "src/gpiote/gpiote.h"

#define SEQUENCE { 0, 1, 2, 3 } // LRGB
#define DEVICE_ID { 7, 2, 0, 0 } // ID = 7200

void blinkLEDs(void)
{
    uint8_t sequence[] = SEQUENCE;
    uint8_t id[] = DEVICE_ID;
    uint8_t blink_count = 0;
    uint8_t seq_counter = 0;
    while(double_click_toggle_flag){ // check the flag for double-click
        for(; seq_counter < NRFX_ARRAY_SIZE(sequence); seq_counter++){
            blink_count = id[sequence[seq_counter]];
            while(double_click_toggle_flag && blink_count > 0){
                switch(sequence[seq_counter]){
                    case 0:
                        gpio_led_toggle(LED_1);
                        break;
                    case 1:
                        gpio_led_toggle(LED_2);
                        break;
                    case 2:
                        gpio_led_toggle(LED_3);
                        break;
                    case 3:
                        gpio_led_toggle(LED_4);
                        break;
                    default:
                        break;
                } // end switch
                blink_count--;
            } // end inner while(blink_count)
        } // end for
        seq_counter = 0;
    } // end while
}

int main(void)
{
    /* Configure board. */
    initialize_board();
    gpiote_init();
    timer_init();

    /* Toggle LEDs. */
    while (true)
    {
        blinkLEDs();
    }
}