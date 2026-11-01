#ifndef COUNTER_H
#define COUNTER_H

#include <stdint.h>

#define COUNTER_MIN_VALUE  (-9999)
#define COUNTER_MAX_VALUE  (9999)
#define COUNTER_DEFAULT_VAL (0)

/**
 * @brief Initialize the digital counter application.
 */
void counter_init(void);

/**
 * @brief Get current counter value.
 */
int32_t counter_get_value(void);

/**
 * @brief Set a custom counter value (clamped between min and max).
 */
void counter_set_value(int32_t val);

/**
 * @brief Increment the counter by step (safe bound checking).
 */
void counter_increment(int32_t step);

/**
 * @brief Decrement the counter by step (safe bound checking).
 */
void counter_decrement(int32_t step);

/**
 * @brief Reset the counter to 0.
 */
void counter_reset(void);

#endif /* COUNTER_H */

