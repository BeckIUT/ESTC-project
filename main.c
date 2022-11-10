#include <stdbool.h>
#include <stdint.h>
#include "src/gpio/led_gpio.h"
#include "src/utils/delay.h"

#define SEQUENCE { 0, 1, 2, 3 } // LRGB
#define DEVICE_ID { 7, 2, 0, 0 }

void blinkLEDs(void)
{
    uint8_t sequence[] = SEQUENCE;
    uint8_t id[] = DEVICE_ID;
    uint8_t blink_count = 0;
    uint8_t seq_counter = 0;
    while(gpio_button_is_pressed()){
        for(; seq_counter < NRFX_ARRAY_SIZE(sequence); seq_counter++){
            blink_count = id[sequence[seq_counter]];
            while(blink_count > 0){
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
                do{ // want to have some pause, so we see LED_OFF
                    nrf_delay_ms(RELEASE_CHECK_INTERVAL_MS);
                } while(gpio_button_is_released()); // end release check
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

    /* Toggle LEDs. */
    while (true)
    {
        blinkLEDs();
    }
}