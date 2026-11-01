#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief LED operation modes
 */
typedef enum {
    LED_MODE_MANUAL = 0,
    LED_MODE_BLINK
} led_mode_t;

/**
 * @brief Hardware GPIO output callback type
 */
typedef void (*led_gpio_callback_t)(bool is_on);

/**
 * @brief Initialize the LED control application.
 */
void led_control_init(void);

/**
 * @brief Turn the LED continuously ON.
 */
void led_control_turn_on(void);

/**
 * @brief Turn the LED OFF.
 */
void led_control_turn_off(void);

/**
 * @brief Toggle the LED state in manual mode.
 */
void led_control_toggle(void);

/**
 * @brief Enable or disable blink mode.
 * @param enable true to start blinking, false for manual mode.
 */
void led_control_set_blink_mode(bool enable);

/**
 * @brief Check if blink mode is active.
 */
bool led_control_is_blink_mode(void);

/**
 * @brief Set the blink interval in milliseconds (clamped between 100ms and 3000ms).
 */
void led_control_set_blink_interval(uint32_t interval_ms);

/**
 * @brief Adjust blink interval by a delta (e.g. +100ms or -100ms).
 */
void led_control_adjust_blink_interval(int32_t delta_ms);

/**
 * @brief Get current blink interval in milliseconds.
 */
uint32_t led_control_get_blink_interval(void);

/**
 * @brief Get current physical/visual illumination state (true if glowing/active).
 */
bool led_control_get_state(void);

/**
 * @brief Set an optional hardware GPIO driver callback.
 */
void led_control_set_gpio_callback(led_gpio_callback_t callback);

/**
 * @brief Periodic update function for blinking and timing.
 * @param current_time_ms Current timestamp in milliseconds.
 */
void led_control_update(uint32_t current_time_ms);

#endif /* LED_CONTROL_H */

