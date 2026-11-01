#include "ui_led.h"
#include "ui_manager.h"
#include "led_control.h"
#include <stdio.h>

typedef struct {
    lv_obj_t *led_indicator;
    lv_obj_t *lbl_status;
    lv_obj_t *btn_blink;
    lv_obj_t *lbl_blink;
    lv_obj_t *lbl_interval;
    lv_timer_t *timer;
} ui_led_ctx_t;

static void update_led_ui(ui_led_ctx_t *ctx)
{
    bool is_on = led_control_get_state();
    bool is_blink = led_control_is_blink_mode();
    uint32_t interval = led_control_get_blink_interval();

    /* Update visual glowing LED */
    if (is_on) {
        lv_obj_set_style_bg_color(ctx->led_indicator, lv_color_hex(0x00E676), 0);
        lv_obj_set_style_border_color(ctx->led_indicator, lv_color_hex(0xB9F6CA), 0);
        lv_obj_set_style_border_width(ctx->led_indicator, 3, 0);
    } else {
        lv_obj_set_style_bg_color(ctx->led_indicator, lv_color_hex(0x1F2A3C), 0);
        lv_obj_set_style_border_color(ctx->led_indicator, lv_color_hex(0x354865), 0);
        lv_obj_set_style_border_width(ctx->led_indicator, 2, 0);
    }

    /* Update status text */
    if (is_blink) {
        char status_str[32];
        snprintf(status_str, sizeof(status_str), "BLINKING (%lums)", (unsigned long)interval);
        lv_label_set_text(ctx->lbl_status, status_str);
        lv_obj_set_style_text_color(ctx->lbl_status, lv_color_hex(0x00E5FF), 0);

        lv_label_set_text(ctx->lbl_blink, "STOP BLINK");
        lv_obj_set_style_bg_color(ctx->btn_blink, lv_color_hex(0x00838F), 0);
    } else {
        if (is_on) {
            lv_label_set_text(ctx->lbl_status, "LED IS ON");
            lv_obj_set_style_text_color(ctx->lbl_status, lv_color_hex(0x00E676), 0);
        } else {
            lv_label_set_text(ctx->lbl_status, "LED IS OFF");
            lv_obj_set_style_text_color(ctx->lbl_status, lv_color_hex(0x7E8D9F), 0);
        }
        lv_label_set_text(ctx->lbl_blink, "BLINK MODE");
        lv_obj_set_style_bg_color(ctx->btn_blink, lv_color_hex(0x28364F), 0);
    }

    /* Update interval display */
    char interval_str[16];
    snprintf(interval_str, sizeof(interval_str), "%lu ms", (unsigned long)interval);
    lv_label_set_text(ctx->lbl_interval, interval_str);
}

static void led_timer_cb(lv_timer_t *timer)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_timer_get_user_data(timer);
    if (ctx != NULL) {
        led_control_update(lv_tick_get());
        update_led_ui(ctx);
    }
}

static void toggle_click_cb(lv_event_t *e)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_event_get_user_data(e);
    if (led_control_is_blink_mode()) {
        led_control_set_blink_mode(false);
    }
    led_control_toggle();
    update_led_ui(ctx);
}

static void blink_click_cb(lv_event_t *e)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_event_get_user_data(e);
    bool current_blink = led_control_is_blink_mode();
    led_control_set_blink_mode(!current_blink);
    update_led_ui(ctx);
}

static void speed_minus_click_cb(lv_event_t *e)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_event_get_user_data(e);
    led_control_adjust_blink_interval(-100);
    update_led_ui(ctx);
}

static void speed_plus_click_cb(lv_event_t *e)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_event_get_user_data(e);
    led_control_adjust_blink_interval(100);
    update_led_ui(ctx);
}

static void screen_delete_cb(lv_event_t *e)
{
    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_event_get_user_data(e);
    if (ctx != NULL) {
        if (ctx->timer != NULL) {
            lv_timer_delete(ctx->timer);
            ctx->timer = NULL;
        }
        lv_free(ctx);
    }
}

lv_obj_t *ui_led_create(void)
{
    lv_obj_t *screen = ui_manager_create_screen_base("LED CONTROL", true);

    ui_led_ctx_t *ctx = (ui_led_ctx_t *)lv_malloc(sizeof(ui_led_ctx_t));
    if (!ctx) return screen;

    /* Indicator Card */
    lv_obj_t *card = lv_obj_create(screen);
    lv_obj_set_size(card, 216, 68);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, 44);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x192131), 0);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0x28364F), 0);
    lv_obj_set_style_pad_all(card, 6, 0);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    /* Round glowing LED badge */
    ctx->led_indicator = lv_obj_create(card);
    lv_obj_set_size(ctx->led_indicator, 36, 36);
    lv_obj_align(ctx->led_indicator, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_set_style_radius(ctx->led_indicator, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_scrollbar_mode(ctx->led_indicator, LV_SCROLLBAR_MODE_OFF);

    /* Status Label */
    ctx->lbl_status = lv_label_create(card);
    lv_label_set_text(ctx->lbl_status, "LED IS OFF");
    lv_obj_set_style_text_color(ctx->lbl_status, lv_color_white(), 0);
    lv_obj_align(ctx->lbl_status, LV_ALIGN_LEFT_MID, 60, 0);

    /* Row 1 Controls: Toggle & Blink mode */
    lv_obj_t *row1 = lv_obj_create(screen);
    lv_obj_set_size(row1, 216, 50);
    lv_obj_align(row1, LV_ALIGN_TOP_MID, 0, 118);
    lv_obj_set_style_bg_opa(row1, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row1, 0, 0);
    lv_obj_set_style_pad_all(row1, 0, 0);
    lv_obj_set_scrollbar_mode(row1, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *btn_toggle = lv_button_create(row1);
    lv_obj_set_size(btn_toggle, 102, 44);
    lv_obj_align(btn_toggle, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_radius(btn_toggle, 8, 0);
    lv_obj_set_style_bg_color(btn_toggle, lv_color_hex(0x00C853), 0);
    lv_obj_add_event_cb(btn_toggle, toggle_click_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_toggle = lv_label_create(btn_toggle);
    lv_label_set_text(lbl_toggle, "TOGGLE");
    lv_obj_set_style_text_color(lbl_toggle, lv_color_white(), 0);
    lv_obj_center(lbl_toggle);

    ctx->btn_blink = lv_button_create(row1);
    lv_obj_set_size(ctx->btn_blink, 102, 44);
    lv_obj_align(ctx->btn_blink, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_radius(ctx->btn_blink, 8, 0);
    lv_obj_set_style_bg_color(ctx->btn_blink, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(ctx->btn_blink, blink_click_cb, LV_EVENT_CLICKED, ctx);

    ctx->lbl_blink = lv_label_create(ctx->btn_blink);
    lv_label_set_text(ctx->lbl_blink, "BLINK MODE");
    lv_obj_set_style_text_color(ctx->lbl_blink, lv_color_white(), 0);
    lv_obj_center(ctx->lbl_blink);

    /* Row 2 Controls: Speed adjustment */
    lv_obj_t *row2 = lv_obj_create(screen);
    lv_obj_set_size(row2, 216, 52);
    lv_obj_align(row2, LV_ALIGN_TOP_MID, 0, 172);
    lv_obj_set_style_bg_color(row2, lv_color_hex(0x192131), 0);
    lv_obj_set_style_radius(row2, 8, 0);
    lv_obj_set_style_border_width(row2, 1, 0);
    lv_obj_set_style_border_color(row2, lv_color_hex(0x28364F), 0);
    lv_obj_set_style_pad_all(row2, 4, 0);
    lv_obj_set_scrollbar_mode(row2, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *btn_minus = lv_button_create(row2);
    lv_obj_set_size(btn_minus, 48, 38);
    lv_obj_align(btn_minus, LV_ALIGN_LEFT_MID, 4, 0);
    lv_obj_set_style_radius(btn_minus, 6, 0);
    lv_obj_set_style_bg_color(btn_minus, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(btn_minus, speed_minus_click_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_minus = lv_label_create(btn_minus);
    lv_label_set_text(lbl_minus, "-100");
    lv_obj_set_style_text_color(lbl_minus, lv_color_hex(0x00E5FF), 0);
    lv_obj_center(lbl_minus);

    ctx->lbl_interval = lv_label_create(row2);
    lv_label_set_text(ctx->lbl_interval, "500 ms");
    lv_obj_set_style_text_color(ctx->lbl_interval, lv_color_white(), 0);
    lv_obj_align(ctx->lbl_interval, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *btn_plus = lv_button_create(row2);
    lv_obj_set_size(btn_plus, 48, 38);
    lv_obj_align(btn_plus, LV_ALIGN_RIGHT_MID, -4, 0);
    lv_obj_set_style_radius(btn_plus, 6, 0);
    lv_obj_set_style_bg_color(btn_plus, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(btn_plus, speed_plus_click_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_plus = lv_label_create(btn_plus);
    lv_label_set_text(lbl_plus, "+100");
    lv_obj_set_style_text_color(lbl_plus, lv_color_hex(0x00E5FF), 0);
    lv_obj_center(lbl_plus);

    /* Timer for blinking state updates (40ms) */
    ctx->timer = lv_timer_create(led_timer_cb, 40, ctx);

    /* Screen cleanup callback */
    lv_obj_add_event_cb(screen, screen_delete_cb, LV_EVENT_DELETE, ctx);

    update_led_ui(ctx);

    return screen;
}

