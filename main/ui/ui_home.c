#include "ui_home.h"
#include "ui_manager.h"

static void app_card_click_cb(lv_event_t *e)
{
    ui_screen_id_t target = (ui_screen_id_t)(uintptr_t)lv_event_get_user_data(e);
    ui_manager_show_screen(target);
}

static void anim_pulse_border_cb(lv_anim_t *a, int32_t val)
{
    lv_obj_set_style_border_opa((lv_obj_t *)a->var, (lv_opa_t)val, 0);
}

static lv_obj_t *create_halloween_card(lv_obj_t *parent, int y_ofs, const char *symbol, const char *title, const char *desc, lv_color_t accent, ui_screen_id_t target)
{
    lv_obj_t *card = lv_button_create(parent);
    lv_obj_set_size(card, 218, 52);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, y_ofs);
    lv_obj_set_style_bg_color(card, COLOR_HAUNT_CARD, 0);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x2B1540), LV_STATE_PRESSED);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, accent, 0);
    lv_obj_set_style_border_opa(card, LV_OPA_60, 0);
    lv_obj_set_style_pad_all(card, 6, 0);
    lv_obj_set_scrollbar_mode(card, LV_SCROLLBAR_MODE_OFF);

    /* Left accent badge */
    lv_obj_t *badge = lv_obj_create(card);
    lv_obj_set_size(badge, 36, 36);
    lv_obj_align(badge, LV_ALIGN_LEFT_MID, 4, 0);
    lv_obj_set_style_bg_color(badge, accent, 0);
    lv_obj_set_style_bg_opa(badge, LV_OPA_30, 0);
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
    lv_obj_set_style_text_color(lbl_desc, COLOR_GHOST_TEXT, 0);
    lv_obj_align(lbl_desc, LV_ALIGN_TOP_LEFT, 50, 24);

    /* Spooky chevron arrow */
    lv_obj_t *lbl_arrow = lv_label_create(card);
    lv_label_set_text(lbl_arrow, LV_SYMBOL_RIGHT);
    lv_obj_set_style_text_color(lbl_arrow, accent, 0);
    lv_obj_align(lbl_arrow, LV_ALIGN_RIGHT_MID, -6, 0);

    lv_obj_add_event_cb(card, app_card_click_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)target);

    return card;
}

lv_obj_t *ui_home_create(void)
{
    lv_obj_t *screen = ui_manager_create_screen_base(NULL, false);

    /* Top Custom Header for Home Screen */
    lv_obj_t *header = lv_obj_create(screen);
    lv_obj_set_size(header, 240, 38);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x130A1C), 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_color(header, COLOR_PUMPKIN_ORANGE, 0);
    lv_obj_set_style_border_width(header, 1, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 4, 0);
    lv_obj_set_scrollbar_mode(header, LV_SCROLLBAR_MODE_OFF);

    /* User Name Branding: mahaboobtech (Glowing Pumpkin Orange) */
    lv_obj_t *lbl_user = lv_label_create(header);
    lv_label_set_text(lbl_user, "mahaboobtech");
    lv_obj_set_style_text_color(lbl_user, COLOR_PUMPKIN_ORANGE, 0);
    lv_obj_align(lbl_user, LV_ALIGN_LEFT_MID, 8, 0);

    /* Battery removed as requested! Replaced with Spooky OS badge */
    lv_obj_t *lbl_tag = lv_label_create(header);
    lv_label_set_text(lbl_tag, "SPOOKY OS");
    lv_obj_set_style_text_color(lbl_tag, COLOR_WITCH_PURPLE, 0);
    lv_obj_align(lbl_tag, LV_ALIGN_RIGHT_MID, -8, 0);

    /* 3 Spooky Halloween App Cards */
    lv_obj_t *card1 = create_halloween_card(
        screen,
        46,
        LV_SYMBOL_PLAY,
        "Ghost Timer",
        "Stopwatch & Laps",
        COLOR_PUMPKIN_ORANGE,
        UI_SCREEN_STOPWATCH
    );

    lv_obj_t *card2 = create_halloween_card(
        screen,
        106,
        LV_SYMBOL_POWER,
        "Witch Torch",
        "LED & Eerie Blink",
        COLOR_GHOST_GREEN,
        UI_SCREEN_LED
    );

    lv_obj_t *card3 = create_halloween_card(
        screen,
        166,
        LV_SYMBOL_EDIT,
        "Soul Counter",
        "Spirits: -9999 to 9999",
        COLOR_WITCH_PURPLE,
        UI_SCREEN_COUNTER
    );

    /* Breathing pulse animation on card1 border for Halloween aura */
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, card1);
    lv_anim_set_values(&a, LV_OPA_30, LV_OPA_COVER);
    lv_anim_set_duration(&a, 1200);
    lv_anim_set_playback_duration(&a, 1200);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_custom_exec_cb(&a, anim_pulse_border_cb);
    lv_anim_start(&a);

    return screen;
}
