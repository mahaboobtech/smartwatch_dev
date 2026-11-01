#include "ui_manager.h"
#include "ui_home.h"
#include "ui_stopwatch.h"
#include "ui_led.h"
#include "ui_counter.h"
#include "stopwatch.h"
#include "led_control.h"
#include "counter.h"

static bool s_is_initialized = false;

static void back_btn_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_manager_go_home();
}

lv_obj_t *ui_manager_create_screen_base(const char *title, bool show_back_button)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x0F141C), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);

    /* Header Bar */
    lv_obj_t *header = lv_obj_create(screen);
    lv_obj_set_size(header, 240, 36);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x161D2B), 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_color(header, lv_color_hex(0x242F43), 0);
    lv_obj_set_style_border_width(header, 1, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 2, 0);
    lv_obj_set_scrollbar_mode(header, LV_SCROLLBAR_MODE_OFF);

    if (show_back_button) {
        lv_obj_t *btn_back = lv_button_create(header);
        lv_obj_set_size(btn_back, 44, 26);
        lv_obj_align(btn_back, LV_ALIGN_LEFT_MID, 6, 0);
        lv_obj_set_style_bg_color(btn_back, lv_color_hex(0x222C3E), 0);
        lv_obj_set_style_radius(btn_back, 6, 0);
        lv_obj_set_style_pad_all(btn_back, 0, 0);
        lv_obj_add_event_cb(btn_back, back_btn_event_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_t *lbl_back = lv_label_create(btn_back);
        lv_label_set_text(lbl_back, LV_SYMBOL_LEFT);
        lv_obj_set_style_text_color(lbl_back, lv_color_hex(0x00E5FF), 0);
        lv_obj_center(lbl_back);
    }

    if (title != NULL) {
        lv_obj_t *lbl_title = lv_label_create(header);
        lv_label_set_text(lbl_title, title);
        lv_obj_set_style_text_color(lbl_title, lv_color_white(), 0);
        if (show_back_button) {
            lv_obj_align(lbl_title, LV_ALIGN_CENTER, 8, 0);
        } else {
            lv_obj_align(lbl_title, LV_ALIGN_CENTER, 0, 0);
        }
    }

    return screen;
}

void ui_manager_init(void)
{
    /* Initialize application logic singletons */
    stopwatch_init(NULL);
    led_control_init();
    counter_init();

    s_is_initialized = true;

    /* Load initial home screen */
    lv_obj_t *home = ui_home_create();
    lv_screen_load(home);
}

void ui_manager_show_screen(ui_screen_id_t screen_id)
{
    if (!s_is_initialized) {
        ui_manager_init();
        return;
    }

    lv_obj_t *next_screen = NULL;

    switch (screen_id) {
        case UI_SCREEN_HOME:
            next_screen = ui_home_create();
            break;
        case UI_SCREEN_STOPWATCH:
            next_screen = ui_stopwatch_create();
            break;
        case UI_SCREEN_LED:
            next_screen = ui_led_create();
            break;
        case UI_SCREEN_COUNTER:
            next_screen = ui_counter_create();
            break;
        default:
            next_screen = ui_home_create();
            break;
    }

    if (next_screen != NULL) {
        /* Auto-delete previous screen after smooth fade */
        lv_screen_load_anim(next_screen, LV_SCREEN_LOAD_ANIM_FADE_IN, 120, 0, true);
    }
}

void ui_manager_go_home(void)
{
    ui_manager_show_screen(UI_SCREEN_HOME);
}

