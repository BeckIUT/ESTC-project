#include "nrf_drv_clock.h"
#include "gpiote.h"
#include "../gpio/led_gpio.h"

#define DEBOUNCE_TIMER      50
#define DOUBLE_CLICK_TIMER  500
#define DOUBLE_CLICK        2
#define RESET               0

static uint32_t bounce_counter = 0;
static uint32_t pressed_count = 0;

APP_TIMER_DEF(debouncing_timer_id);
APP_TIMER_DEF(double_click_timer_id);

void gpiote_init(void)
{
    ret_code_t err_code;
    err_code = nrfx_gpiote_init();
    APP_ERROR_CHECK(err_code);
    
    nrfx_gpiote_in_config_t in_config = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;
    err_code = nrfx_gpiote_in_init(BUTTON_1, &in_config, button_toggle_handler);
    APP_ERROR_CHECK(err_code);

    nrfx_gpiote_in_event_enable(BUTTON_1, true);
}

void button_toggle_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    /**
     *  if bounce counter == 0 start timer, debouncing cases will be recorded in counter
     * when debouncing timer expires reset counter 
     * and check press/release with pin check
    */
   if(bounce_counter == RESET){
        app_timer_start(debouncing_timer_id, APP_TIMER_TICKS(DEBOUNCE_TIMER), NULL);
        if(pressed_count == RESET) // toggle will be reset if no double click detected in the handler
            app_timer_start(double_click_timer_id, APP_TIMER_TICKS(DOUBLE_CLICK_TIMER), NULL);
    }
    bounce_counter++;
}

static void lfclk_init(void)
{
    APP_ERROR_CHECK(nrf_drv_clock_init());
    nrf_drv_clock_lfclk_request(NULL);
}

void timer_init(void)
{
    lfclk_init();
    ret_code_t err_code;
    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&debouncing_timer_id, APP_TIMER_MODE_SINGLE_SHOT, debounce_timer_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&double_click_timer_id, APP_TIMER_MODE_SINGLE_SHOT, double_click_timer_handler);
    APP_ERROR_CHECK(err_code);

    double_click_toggle_flag = false;
}

void debounce_timer_handler(void * p_context)
{
    if(gpio_button_is_pressed())
        pressed_count++;
    bounce_counter = RESET; // reset counter for next timer
}

void double_click_timer_handler(void * p_context)
{
    if(pressed_count == DOUBLE_CLICK) // now long press does not affect double click
        double_click_toggle_flag = !double_click_toggle_flag;
    pressed_count = RESET;
}