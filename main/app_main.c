#include "lvgl.h"

// Create the smartwatch home screen
static void create_home_screen(void)
{
    lv_obj_t *screen = lv_screen_active();

    // Background
    lv_obj_set_style_bg_color(
        screen,
        lv_color_hex(0x10131C),
        0
    );

    // Main title
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "MY SMARTWATCH");
    lv_obj_set_style_text_color(
        title, lv_color_white(), 0
    );
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // Stopwatch button
    lv_obj_t *stopwatch = lv_button_create(screen);
    lv_obj_set_size(stopwatch, 85, 65);
    lv_obj_align(stopwatch, LV_ALIGN_CENTER, -48, -15);

    lv_obj_t *label1 = lv_label_create(stopwatch);
    lv_label_set_text(label1, "STOPWATCH");
    lv_obj_center(label1);

    // LED button
    lv_obj_t *led = lv_button_create(screen);
    lv_obj_set_size(led, 85, 65);
    lv_obj_align(led, LV_ALIGN_CENTER, 48, -15);

    lv_obj_t *label2 = lv_label_create(led);
    lv_label_set_text(label2, "LED");
    lv_obj_center(label2);

    // Counter button
    lv_obj_t *counter = lv_button_create(screen);
    lv_obj_set_size(counter, 150, 55);
    lv_obj_align(counter, LV_ALIGN_CENTER, 0, 65);

    lv_obj_t *label3 = lv_label_create(counter);
    lv_label_set_text(label3, "COUNTER");
    lv_obj_center(label3);
}

// Required LVGL Live Preview entry point
#ifdef LVGL_LIVE_PREVIEW
void lvgl_live_preview_init(void)
{
    create_home_screen();
}
#endif

// ESP-IDF firmware entry point
void app_main(void)
{
    // Will initialize display, touch, and UI tasks in Stage 2
}
