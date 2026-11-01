#include "ui_counter.h"
#include "ui_manager.h"
#include "counter.h"
#include <stdio.h>

typedef struct {
    lv_obj_t *lbl_value;
} ui_counter_ctx_t;

static void update_counter_ui(ui_counter_ctx_t *ctx)
{
    int32_t val = counter_get_value();
    char val_str[16];
    snprintf(val_str, sizeof(val_str), "%ld", (long)val);
    lv_label_set_text(ctx->lbl_value, val_str);
}

static void inc_btn_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    counter_increment(1);
    update_counter_ui(ctx);
}

static void dec_btn_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    counter_decrement(1);
    update_counter_ui(ctx);
}

static void inc10_btn_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    counter_increment(10);
    update_counter_ui(ctx);
}

static void dec10_btn_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    counter_decrement(10);
    update_counter_ui(ctx);
}

static void reset_btn_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    counter_reset();
    update_counter_ui(ctx);
}

static void screen_delete_cb(lv_event_t *e)
{
    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_event_get_user_data(e);
    if (ctx != NULL) {
        lv_free(ctx);
    }
}

lv_obj_t *ui_counter_create(void)
{
    lv_obj_t *screen = ui_manager_create_screen_base("COUNTER", true);

    ui_counter_ctx_t *ctx = (ui_counter_ctx_t *)lv_malloc(sizeof(ui_counter_ctx_t));
    if (!ctx) return screen;

    /* Value Display Card */
    lv_obj_t *card = lv_obj_create(screen);
    lv_obj_set_size(card, 216, 68);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, 44);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x192131), 0);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0x28364F), 0);
    lv_obj_set_style_pad_all(card, 4, 0);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    ctx->lbl_value = lv_label_create(card);
    lv_label_set_text(ctx->lbl_value, "0");
    lv_obj_set_style_text_color(ctx->lbl_value, lv_color_hex(0xFFB300), 0);
    lv_obj_align(ctx->lbl_value, LV_ALIGN_CENTER, 0, -6);

    lv_obj_t *lbl_limits = lv_label_create(card);
    lv_label_set_text(lbl_limits, "Limits: [-9999 to 9999]");
    lv_obj_set_style_text_color(lbl_limits, lv_color_hex(0x576579), 0);
    lv_obj_align(lbl_limits, LV_ALIGN_BOTTOM_MID, 0, -2);

    /* Primary Row: -1 / +1 */
    lv_obj_t *row1 = lv_obj_create(screen);
    lv_obj_set_size(row1, 216, 50);
    lv_obj_align(row1, LV_ALIGN_TOP_MID, 0, 118);
    lv_obj_set_style_bg_opa(row1, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row1, 0, 0);
    lv_obj_set_style_pad_all(row1, 0, 0);
    lv_obj_set_scrollbar_mode(row1, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *btn_dec = lv_button_create(row1);
    lv_obj_set_size(btn_dec, 102, 44);
    lv_obj_align(btn_dec, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_radius(btn_dec, 8, 0);
    lv_obj_set_style_bg_color(btn_dec, lv_color_hex(0xD32F2F), 0);
    lv_obj_add_event_cb(btn_dec, dec_btn_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_dec = lv_label_create(btn_dec);
    lv_label_set_text(lbl_dec, "- 1");
    lv_obj_set_style_text_color(lbl_dec, lv_color_white(), 0);
    lv_obj_center(lbl_dec);

    lv_obj_t *btn_inc = lv_button_create(row1);
    lv_obj_set_size(btn_inc, 102, 44);
    lv_obj_align(btn_inc, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_radius(btn_inc, 8, 0);
    lv_obj_set_style_bg_color(btn_inc, lv_color_hex(0x00C853), 0);
    lv_obj_add_event_cb(btn_inc, inc_btn_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_inc = lv_label_create(btn_inc);
    lv_label_set_text(lbl_inc, "+ 1");
    lv_obj_set_style_text_color(lbl_inc, lv_color_white(), 0);
    lv_obj_center(lbl_inc);

    /* Secondary Row: -10 / RESET / +10 */
    lv_obj_t *row2 = lv_obj_create(screen);
    lv_obj_set_size(row2, 216, 48);
    lv_obj_align(row2, LV_ALIGN_TOP_MID, 0, 174);
    lv_obj_set_style_bg_opa(row2, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row2, 0, 0);
    lv_obj_set_style_pad_all(row2, 0, 0);
    lv_obj_set_scrollbar_mode(row2, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *btn_dec10 = lv_button_create(row2);
    lv_obj_set_size(btn_dec10, 60, 40);
    lv_obj_align(btn_dec10, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_radius(btn_dec10, 6, 0);
    lv_obj_set_style_bg_color(btn_dec10, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(btn_dec10, dec10_btn_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_dec10 = lv_label_create(btn_dec10);
    lv_label_set_text(lbl_dec10, "-10");
    lv_obj_set_style_text_color(lbl_dec10, lv_color_hex(0x00E5FF), 0);
    lv_obj_center(lbl_dec10);

    lv_obj_t *btn_rst = lv_button_create(row2);
    lv_obj_set_size(btn_rst, 80, 40);
    lv_obj_align(btn_rst, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(btn_rst, 6, 0);
    lv_obj_set_style_bg_color(btn_rst, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(btn_rst, reset_btn_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_rst = lv_label_create(btn_rst);
    lv_label_set_text(lbl_rst, "RESET");
    lv_obj_set_style_text_color(lbl_rst, lv_color_white(), 0);
    lv_obj_center(lbl_rst);

    lv_obj_t *btn_inc10 = lv_button_create(row2);
    lv_obj_set_size(btn_inc10, 60, 40);
    lv_obj_align(btn_inc10, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_radius(btn_inc10, 6, 0);
    lv_obj_set_style_bg_color(btn_inc10, lv_color_hex(0x28364F), 0);
    lv_obj_add_event_cb(btn_inc10, inc10_btn_cb, LV_EVENT_CLICKED, ctx);

    lv_obj_t *lbl_inc10 = lv_label_create(btn_inc10);
    lv_label_set_text(lbl_inc10, "+10");
    lv_obj_set_style_text_color(lbl_inc10, lv_color_hex(0x00E5FF), 0);
    lv_obj_center(lbl_inc10);

    lv_obj_add_event_cb(screen, screen_delete_cb, LV_EVENT_DELETE, ctx);

    update_counter_ui(ctx);

    return screen;
}

