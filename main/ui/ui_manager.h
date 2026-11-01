#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "lvgl.h"
#include <stdbool.h>

/* Halloween Spooky Theme Colors */
#define COLOR_HAUNT_BG       lv_color_hex(0x090510) /* Deep obsidian purple-black */
#define COLOR_HAUNT_CARD     lv_color_hex(0x160D22) /* Haunted crypt card */
#define COLOR_HAUNT_BORDER   lv_color_hex(0x2E1A42) /* Spooky violet border */
#define COLOR_PUMPKIN_ORANGE lv_color_hex(0xFF6D00) /* Jack-o'-Lantern neon orange */
#define COLOR_PUMPKIN_AMBER  lv_color_hex(0xFF9100) /* Warm glowing amber */
#define COLOR_WITCH_PURPLE   lv_color_hex(0x9C27B0) /* Witch mysticism purple */
#define COLOR_GHOST_GREEN    lv_color_hex(0x00E676) /* Ectoplasm slime green */
#define COLOR_BLOOD_CRIMSON  lv_color_hex(0xD50000) /* Blood crimson red */
#define COLOR_GHOST_TEXT     lv_color_hex(0xB0A0BE) /* Eerie lavender-gray text */

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
 * @brief Transition to a specific screen with smooth animation.
 * @param screen_id Target screen ID.
 */
void ui_manager_show_screen(ui_screen_id_t screen_id);

/**
 * @brief Navigate back to the home screen.
 */
void ui_manager_go_home(void);

/**
 * @brief Helper to create a standardized Halloween screen base with dark background,
 *        header bar, title, mahaboobtech tag, and optional Back button.
 * @param title Title displayed in header.
 * @param show_back_button True to include the interactive Back button.
 * @return Pointer to screen object.
 */
lv_obj_t *ui_manager_create_screen_base(const char *title, bool show_back_button);

#endif /* UI_MANAGER_H */
