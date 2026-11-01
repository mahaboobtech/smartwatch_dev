#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Stopwatch operational states
 */
typedef enum {
    STOPWATCH_STATE_RESET = 0,
    STOPWATCH_STATE_RUNNING,
    STOPWATCH_STATE_PAUSED
} stopwatch_state_t;

/**
 * @brief Time retrieval function pointer type (returns millisecond tick)
 */
typedef uint32_t (*stopwatch_time_fn_t)(void);

/**
 * @brief Initialize the stopwatch application logic.
 * @param time_fn Pointer to millisecond tick provider function. If NULL, default ticker is used.
 */
void stopwatch_init(stopwatch_time_fn_t time_fn);

/**
 * @brief Start or resume the stopwatch.
 */
void stopwatch_start(void);

/**
 * @brief Pause the running stopwatch.
 */
void stopwatch_pause(void);

/**
 * @brief Resume a paused stopwatch.
 */
void stopwatch_resume(void);

/**
 * @brief Stop and reset the stopwatch back to 0.
 */
void stopwatch_reset(void);

/**
 * @brief Get current operational state.
 */
stopwatch_state_t stopwatch_get_state(void);

/**
 * @brief Get total elapsed time in milliseconds.
 */
uint32_t stopwatch_get_elapsed_ms(void);

/**
 * @brief Break down elapsed time into minutes, seconds, and milliseconds.
 * @param out_min Pointer to store minutes.
 * @param out_sec Pointer to store seconds (0-59).
 * @param out_ms Pointer to store fractional milliseconds (0-999).
 */
void stopwatch_get_time_components(uint32_t *out_min, uint32_t *out_sec, uint32_t *out_ms);

#endif /* STOPWATCH_H */

