
idf_component_register(
    SRCS
        "app_main.c"
        "ui/ui_manager.c"
        "ui/ui_home.c"
        "ui/ui_stopwatch.c"
        "ui/ui_led.c"
        "ui/ui_counter.c"
        "applications/stopwatch.c"
        "applications/led_control.c"
        "applications/counter.c"

    INCLUDE_DIRS
        "."
        "ui"
        "applications"
)
