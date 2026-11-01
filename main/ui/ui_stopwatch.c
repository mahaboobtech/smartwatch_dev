#include "ui_stopwatch.h"
#include "ui_manager.h"
#include "stopwatch.h"
#include <stdio.h>

typedef struct {
    lv_obj_t *lbl_time;
    lv_obj_t *lbl_status;
    lv_obj_t *btn_start_stop;
    lv_obj_t *lbl_start_stop;
    lv_timer_t *timer;
} ui_stopwatch_ctx_t;

static void update_stopwatch_ui(ui_stopwatch_ctx_t *ctx)
{
    uint32_t min = 0, sec = 0, ms = 0;
    stopwatch_get_time_components(&min, &sec, &ms);
    uint32_t hundredths = ms / 10;

    char time_str[32];
    snprintf(time_str, sizeof(time_str), "%02lu:%02lu.%02lu", (unsigned long)min, (unsigned long)sec, (unsigned long)hundredths);
    lv_label_set_text(ctx->lbl_time, time_str);

    stopwatch_state_t state = stopwatch_get_state();
    if (state == STOPWATCH_STATE_RUNNING) {
        lv_label_set_text(ctx->lbl_status, "HAUNTING...");
        lv_obj_set_style_text_color(ctx->lbl_status, COLOR_GHOST_GREEN, 0);
        lv_label_set_text(ctx->lbl_start_stop, "FREEZE");
        lv_obj_set_style_bg_color(ctx->btn_start_stop, COLOR_BLOOD_CRIMSON, 0);
    } else if (state == STOPWATCH_STATE_PAUSED) {
        lv_label_set_text(ctx->lbl_status, "TIME FROZEN");
        lv_obj_set_style_text_color(ctx->lbl_status, COLOR_PUMPKIN_AMBER, 0);
        lv_label_set_text(ctx->lbl_start_stop, "RESUME");
        lv_obj_set_style_bg_color(ctx->btn_start_stop, COLOR_PUMPKIN_ORANGE, 0);
    } else {
        lv_label_set_text(ctx->lbl_status, "SPIRIT ASLEEP");
        lv_obj_set_style_text_color(ctx->lbl_status, COLOR_GHOST_TEXT, 0);
        lv_label_set_text(ctx->lbl_start_stop, "HAUNT");
        lv_obj_set_style_bg_color(ctx->btn_start_stop, COLOR_PUMPKIN_ORANGE, 0);
    }
}

static void stopwatch_timer_cb(lv_timer_t *timer)
{
    ui_stopwatch_ctx_t *ctx = (ui_stopwatch_ctx_t *)lv_timer_get_user_data(timer);
    if (ctx != NULL) {
        update_stopwatch_ui(ctx);
    }
}

static void start_stop_click_cb(lv_event_t *e)
{
    ui_stopwatch_ctx_t *ctx = (ui_stopwatch_ctx_t *)lv_event_get_user_data(e);
    stopwatch_state_t state = stopwatch_get_state();

    if (state == STOPWATCH_STATE_RUNNING) {
        stopwatch_pause();
    } else if (state == STOPWATCH_STATE_PAUSED) {
        stopwatch_resume();
    } else {
        stopwatch_start();
    }

    update_stopwatch_ui(ctx);
}

static void reset_click_cb(lv_event_t *e)
{
    ui_stopwatch_ctx_t *ctx = (ui_stopwatch_ctx_t *)lv_event_get_user_data(e);
    stopwatch_reset();
    update_stopwatch_ui(ctx);
}

static void screen_delete_cb(lv_event_t *e)
{
    ui_stopwatch_ctx_t *ctx = (ui_stopwatch_ctx_t *)lv_event_get_user_data(e);
    if (ctx != NULL) {
        if (ctx->timer != NULL) {
            lv_timer_delete(ctx->timer);
            ctx->timer = NULL;
        }
        lv_free(ctx);
    }
}

lv_obj_t *ui_stopwatch_create(void)
{
    lv_obj_t *screen = ui_manager_create_screen_base("GHOST TIMER", true);

    ui_stopwatch_ctx_t *ctx = (ui_stopwatch_ctx_t *)lv_malloc(sizeof(ui_stopwatch_ctx_t));
    if (!ctx) return screen;

    /* Spooky Time Display Card */
    lv_obj_t *card = lv_obj_create(screen);
    lv_obj_set_size(card, 218, 88);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, 48);
    lv_obj_set_style_bg_color(card, COLOR_HAUNT_CARD, 0);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, COLOR_PUMPKIN_ORANGE, 0);
    lv_obj_set_style_pad_all(card, 6, 0);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    ctx->lbl_time = lv_label_create(card);
    lv_label_set_text(ctx->lbl_time, "00:00.00");
    lv_obj_set_style_text_color(ctx->lbl_time, COLOR_PUMPKIN_AMBER, 0);
    lv_obj_align(ctx->lbl_time, LV_ALIGN_CENTER, 0, -8);

    ctx->lbl_status = lv_label_create(card);
    lv_label_set_text(ctx->lbl_status, "SPIRIT ASLEEP");
    lv_obj_set_style_text_color(ctx->lbl_status, COLOR_GHOST_TEXT, 0);
    lv_obj_align(ctx->lbl_status, LV_ALIGN_BOTTOM_MID, 0, -4);

    /* Controls container */
    lv_obj_t *controls = lv_obj_create(screen);
    lv_obj_set_size(controls, 218, 70);
    lv_obj_align(controls, LV_ALIGN_TOP_MID, 0, 148);
    lv_obj_set_style_bg_opa(controls, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(controls, 0, 0);
    lv_obj_set_style_pad_all(controls, 0, 0);
    lv_obj_set_scrollbar_mode(controls, LV_SCROLLBAR_MODE_OFF);

    /* HAUNT / FREEZE button */
    ctx->btn_start_stop = lv_button_create(controls);
    lv_obj_set_size(ctx->btn_start_stop, 104, 54);
    lv_obj_align(ctx->btn_start_stop, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_radius(ctx->btn_start_stop, 10, 0);
    lv_obj_set_style_bg_color(ctx->btn_start_stop, COLOR_PUMPKIN_ORANGE, 0);
    lv_obj_add_event_cb(ctx->btn_start_stop, start_stop_click_cb, LV_EVENT_CLICKED, ctx);

    ctx->lbl_start_stop = lv_label_create(ctx->btn_start_stop);
    lv_label_set_text(ctx->lbl_start_stop, "HAUNT");
    lv_obj_set_style_text_color(ctx->lbl_start_stop, lv_color_white(), 0);
    lv_obj_center(ctx->lbl_start_stop);

    /* PURGE (RESET) button */
    lv_obj_t *btn_reset = lv_button_create(controls);
    lv_obj_set_size(btn_reset, 104, 54);
    lv_obj_align(btn_reset, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_radius(btn_reset, 10, 0);
    lv_obj_set_style_bg_color(btn_reset, lv_color_hex(0x28153B), 0);
    lv_obj_set_style_border_width(btn_reset, 1, 0);
    lv_obj_set_style_border_color(btn_reset, COLOR_WITCH_PURPLE, 0);
    lv_obj_add_event_cb(btn_reset, reset_click_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_reset = lv_label_create(btn_reset);
    lv_label_set_text(lbl_reset, "PURGE");
    lv_obj_set_style_text_color(lbl_reset, COLOR_WITCH_PURPLE, 0);
    lv_obj_center(lbl_reset);

    /* Timer for 40ms updates */
    ctx->timer = lv_timer_create(stopwatch_timer_cb, 40, ctx);

    lv_obj_add_event_cb(screen, screen_delete_cb, LV_EVENT_DELETE, ctx);

    update_stopwatch_ui(ctx);

    return screen;
}
