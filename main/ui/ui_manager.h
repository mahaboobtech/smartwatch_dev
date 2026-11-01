#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "lvgl.h"
#include <stdbool.h>

/**
 * @brief Identifiers for smartwatch screens
 */
typedef enum {
    UI_SCREEN_HOME = 0,
    UI_SCREEN_STOPWATCH,
    UI_SCREEN_LED,
    UI_SCREEN_COUNTER
} ui_screen_id_t;

/**
 * @brief Initialize the smartwatch UI manager and load the home screen.
 */
void ui_manager_init(void);

/**
 * @brief Transition to a specific screen.
 * @param screen_id Target screen ID.
 */
void ui_manager_show_screen(ui_screen_id_t screen_id);

/**
 * @brief Navigate back to the home screen.
 */
void ui_manager_go_home(void);

/**
 * @brief Helper to create a standardized screen base with dark background,
 *        header bar, title, and optional Back button.
 * @param title Title displayed in header.
 * @param show_back_button True to include the interactive Back button.
 * @return Pointer to screen object.
 */
lv_obj_t *ui_manager_create_screen_base(const char *title, bool show_back_button);

#endif /* UI_MANAGER_H */

