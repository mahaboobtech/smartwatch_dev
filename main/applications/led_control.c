#include "led_control.h"
#include <stddef.h>

#define LED_MIN_INTERVAL_MS   100
#define LED_MAX_INTERVAL_MS   3000
#define LED_DEFAULT_INTERVAL  500

static led_mode_t s_mode = LED_MODE_MANUAL;
static bool s_is_on = false;
static uint32_t s_interval_ms = LED_DEFAULT_INTERVAL;
static uint32_t s_last_toggle_tick = 0;
static led_gpio_callback_t s_gpio_cb = NULL;

static void notify_state_change(void)
{
    if (s_gpio_cb != NULL) {
        s_gpio_cb(s_is_on);
    }
}

void led_control_init(void)
{
    s_mode = LED_MODE_MANUAL;
    s_is_on = false;
    s_interval_ms = LED_DEFAULT_INTERVAL;
    s_last_toggle_tick = 0;
    notify_state_change();
}

void led_control_turn_on(void)
{
    s_mode = LED_MODE_MANUAL;
    s_is_on = true;
    notify_state_change();
}

void led_control_turn_off(void)
{
    s_mode = LED_MODE_MANUAL;
    s_is_on = false;
    notify_state_change();
}

void led_control_toggle(void)
{
    s_mode = LED_MODE_MANUAL;
    s_is_on = !s_is_on;
    notify_state_change();
}

void led_control_set_blink_mode(bool enable)
{
    s_mode = enable ? LED_MODE_BLINK : LED_MODE_MANUAL;
    if (s_mode == LED_MODE_MANUAL) {
        s_is_on = false;
        notify_state_change();
    }
}

bool led_control_is_blink_mode(void)
{
    return s_mode == LED_MODE_BLINK;
}

void led_control_set_blink_interval(uint32_t interval_ms)
{
    if (interval_ms < LED_MIN_INTERVAL_MS) {
        interval_ms = LED_MIN_INTERVAL_MS;
    } else if (interval_ms > LED_MAX_INTERVAL_MS) {
        interval_ms = LED_MAX_INTERVAL_MS;
    }
    s_interval_ms = interval_ms;
}

void led_control_adjust_blink_interval(int32_t delta_ms)
{
    int32_t new_interval = (int32_t)s_interval_ms + delta_ms;
    if (new_interval < LED_MIN_INTERVAL_MS) {
        new_interval = LED_MIN_INTERVAL_MS;
    } else if (new_interval > LED_MAX_INTERVAL_MS) {
        new_interval = LED_MAX_INTERVAL_MS;
    }
    s_interval_ms = (uint32_t)new_interval;
}

uint32_t led_control_get_blink_interval(void)
{
    return s_interval_ms;
}

bool led_control_get_state(void)
{
    return s_is_on;
}

void led_control_set_gpio_callback(led_gpio_callback_t callback)
{
    s_gpio_cb = callback;
    notify_state_change();
}

void led_control_update(uint32_t current_time_ms)
{
    if (s_mode == LED_MODE_BLINK) {
        if (current_time_ms - s_last_toggle_tick >= s_interval_ms) {
            s_last_toggle_tick = current_time_ms;
            s_is_on = !s_is_on;
            notify_state_change();
        }
    }
}

