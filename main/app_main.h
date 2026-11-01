#ifndef APP_MAIN_H
#define APP_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ESP-IDF firmware entry point.
 */
void app_main(void);

#ifdef LVGL_LIVE_PREVIEW
/**
 * @brief Required entry point for the LVGL Live Preview simulator.
 */
void lvgl_live_preview_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* APP_MAIN_H */

