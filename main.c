#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"

#define DEVICE_ID 27 // inverted DEVICE ID for ease of implementation, actual ID 7200
#define PAUSE_MS 200
#define LED_NUMBER 4

void blinkLEDs()
{
    uint32_t id = DEVICE_ID;
    for(uint32_t led_count = 0; led_count < LED_NUMBER; led_count++)
    {
        uint32_t blink_count = id%10;
        id /= 10;
        
        if(blink_count == 0) { // no blink
            nrf_delay_ms(PAUSE_MS);
            continue;
        }


        for (; blink_count > 0; blink_count--)
        {
            bsp_board_led_on(led_count);
            nrf_delay_ms(PAUSE_MS);
            bsp_board_led_off(led_count);
            nrf_delay_ms(PAUSE_MS);

        }
        nrf_delay_ms(5*PAUSE_MS);    
    }
}

int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Toggle LEDs. */
    while (true)
    {
        blinkLEDs();
    }
}