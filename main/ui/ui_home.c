#include "ui_home.h"
#include "ui_manager.h"

static void app_card_click_cb(lv_event_t *e)
{
    ui_screen_id_t target = (ui_screen_id_t)(uintptr_t)lv_event_get_user_data(e);
    ui_manager_show_screen(target);
}

static lv_obj_t *create_launcher_card(lv_obj_t *parent, int y_ofs, const char *symbol, const char *title, const char *desc, lv_color_t accent, ui_screen_id_t target)
{
    lv_obj_t *card = lv_button_create(parent);
    lv_obj_set_size(card, 216, 52);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, y_ofs);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x192131), 0);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x243046), LV_STATE_PRESSED);
    lv_obj_set_style_radius(card, 10, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0x28364F), 0);
    lv_obj_set_style_pad_all(card, 6, 0);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    /* Left accent badge */
    lv_obj_t *badge = lv_obj_create(card);
    lv_obj_set_size(badge, 36, 36);
    lv_obj_align(badge, LV_ALIGN_LEFT_MID, 4, 0);
    lv_obj_set_style_bg_color(badge, accent, 0);
    lv_obj_set_style_bg_opa(badge, LV_OPA_20, 0);
    lv_obj_set_style_border_width(badge, 1, 0);
    lv_obj_set_style_border_color(badge, accent, 0);
    lv_obj_set_style_radius(badge, 8, 0);
    lv_obj_set_scrollbar_mode(badge, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *lbl_icon = lv_label_create(badge);
    lv_label_set_text(lbl_icon, symbol);
    lv_obj_set_style_text_color(lbl_icon, accent, 0);
    lv_obj_center(lbl_icon);

    /* Card Title */
    lv_obj_t *lbl_title = lv_label_create(card);
    lv_label_set_text(lbl_title, title);
    lv_obj_set_style_text_color(lbl_title, lv_color_white(), 0);
    lv_obj_align(lbl_title, LV_ALIGN_TOP_LEFT, 50, 6);

    /* Card Subtitle */
    lv_obj_t *lbl_desc = lv_label_create(card);
    lv_label_set_text(lbl_desc, desc);
    lv_obj_set_style_text_color(lbl_desc, lv_color_hex(0x7E8D9F), 0);
    lv_obj_align(lbl_desc, LV_ALIGN_TOP_LEFT, 50, 24);

    /* Chevron right */
    lv_obj_t *lbl_arrow = lv_label_create(card);
    lv_label_set_text(lbl_arrow, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_color(lbl_arrow, lv_color_hex(0x576476), 0);
    lv_obj_align(lbl_arrow, LV_ALIGN_RIGHT_MID, -6, 0);

    lv_obj_add_event_cb(card, app_card_click_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)target);

    return card;
}

lv_obj_t *ui_home_create(void)
{
    lv_obj_t *screen = ui_manager_create_screen_base("SMARTWATCH", false);

    /* Battery / Status indicator in top right of header */
    lv_obj_t *status_lbl = lv_label_create(screen);
    lv_label_set_text(status_lbl, LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_style_text_color(status_lbl, lv_color_hex(0x00E676), 0);
    lv_obj_align(status_lbl, LV_ALIGN_TOP_RIGHT, -10, 10);

    /* 3 App Launcher Cards */
    create_launcher_card(
        screen,
        46,
        LV_SYMBOL_IMAGE,   /* Or clock/timer representation */
        "Stopwatch",
        "Timer & Lap",
        lv_color_hex(0x00E5FF),
        UI_SCREEN_STOPWATCH
    );

    create_launcher_card(
        screen,
        106,
        LV_SYMBOL_POWER,
        "LED Control",
        "GPIO26 & Blink",
        lv_color_hex(0x00E676),
        UI_SCREEN_LED
    );

    create_launcher_card(
        screen,
        166,
        LV_SYMBOL_EDIT,
        "Digital Counter",
        "Tally & Steps",
        lv_color_hex(0xFFB300),
        UI_SCREEN_COUNTER
    );

    return screen;
}

