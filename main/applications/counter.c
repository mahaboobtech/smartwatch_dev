#include "counter.h"

static int32_t s_count = COUNTER_DEFAULT_VAL;

void counter_init(void)
{
    s_count = COUNTER_DEFAULT_VAL;
}

int32_t counter_get_value(void)
{
    return s_count;
}

void counter_set_value(int32_t val)
{
    if (val < COUNTER_MIN_VALUE) {
        val = COUNTER_MIN_VALUE;
    } else if (val > COUNTER_MAX_VALUE) {
        val = COUNTER_MAX_VALUE;
    }
    s_count = val;
}

void counter_increment(int32_t step)
{
    int64_t next = (int64_t)s_count + step;
    if (next > COUNTER_MAX_VALUE) {
        next = COUNTER_MAX_VALUE;
    }
    s_count = (int32_t)next;
}

void counter_decrement(int32_t step)
{
    int64_t next = (int64_t)s_count - step;
    if (next < COUNTER_MIN_VALUE) {
        next = COUNTER_MIN_VALUE;
    }
    s_count = (int32_t)next;
}

void counter_reset(void)
{
    s_count = COUNTER_DEFAULT_VAL;
}

