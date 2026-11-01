#include "stopwatch.h"
#include <stddef.h>

/* Forward declare lv_tick_get if needed as default time provider */
extern uint32_t lv_tick_get(void);

static stopwatch_state_t s_state = STOPWATCH_STATE_RESET;
static stopwatch_time_fn_t s_time_fn = NULL;
static uint32_t s_start_tick = 0;
static uint32_t s_accumulated_ms = 0;

static uint32_t get_current_tick(void)
{
    if (s_time_fn != NULL) {
        return s_time_fn();
    }
    return lv_tick_get();
}

void stopwatch_init(stopwatch_time_fn_t time_fn)
{
    s_time_fn = time_fn;
    s_state = STOPWATCH_STATE_RESET;
    s_start_tick = 0;
    s_accumulated_ms = 0;
}

void stopwatch_start(void)
{
    if (s_state == STOPWATCH_STATE_RESET) {
        s_accumulated_ms = 0;
        s_start_tick = get_current_tick();
        s_state = STOPWATCH_STATE_RUNNING;
    } else if (s_state == STOPWATCH_STATE_PAUSED) {
        stopwatch_resume();
    }
}

void stopwatch_pause(void)
{
    if (s_state == STOPWATCH_STATE_RUNNING) {
        uint32_t now = get_current_tick();
        s_accumulated_ms += (now - s_start_tick);
        s_state = STOPWATCH_STATE_PAUSED;
    }
}

void stopwatch_resume(void)
{
    if (s_state == STOPWATCH_STATE_PAUSED) {
        s_start_tick = get_current_tick();
        s_state = STOPWATCH_STATE_RUNNING;
    }
}

void stopwatch_reset(void)
{
    s_state = STOPWATCH_STATE_RESET;
    s_start_tick = 0;
    s_accumulated_ms = 0;
}

stopwatch_state_t stopwatch_get_state(void)
{
    return s_state;
}

uint32_t stopwatch_get_elapsed_ms(void)
{
    if (s_state == STOPWATCH_STATE_RUNNING) {
        uint32_t now = get_current_tick();
        return s_accumulated_ms + (now - s_start_tick);
    }
    return s_accumulated_ms;
}

void stopwatch_get_time_components(uint32_t *out_min, uint32_t *out_sec, uint32_t *out_ms)
{
    uint32_t total = stopwatch_get_elapsed_ms();
    uint32_t ms = total % 1000;
    uint32_t total_sec = total / 1000;
    uint32_t sec = total_sec % 60;
    uint32_t min = total_sec / 60;

    if (out_min) *out_min = min;
    if (out_sec) *out_sec = sec;
    if (out_ms)  *out_ms  = ms;
}

