#include "app_main.h"
#include "lvgl.h"
#include "ui_manager.h"

#ifdef LVGL_LIVE_PREVIEW
/**
 * @brief Required entry point for the LVGL Live Preview simulator.
 *        Called automatically by the preview extension in VS Code.
 */
void lvgl_live_preview_init(void)
{
    ui_manager_init();
}
#endif

/**
 * @brief ESP-IDF firmware entry point.
 */
void app_main(void)
{
    /* Initialize UI and application subsystem */
    ui_manager_init();

    /* In Stage 2, this will initialize display SPI, touch I2C,
     * and start FreeRTOS tasks (UI Task, Hardware Task, etc.)
     */
}
