# 🎃 ESP32 Smartwatch – Spooky OS (240×240 Touchscreen UI)

A modular, lightweight embedded smartwatch touchscreen interface built with **ESP-IDF**, **LVGL 9**, and **FreeRTOS**, featuring a **Halloween "Spooky OS" theme** by **mahaboobtech**.

Designed for rapid development: you can test, modify, and preview the entire UI on your PC with **zero hardware required** using the LVGL Live Preview simulator, and then flash it directly to an **ESP32 DevKit V1** with a 240×240 touchscreen display!

---

## ⚡ Quick Start (No Hardware Required!)

Run the interactive smartwatch UI on your PC in under 2 minutes:

### Step 1: Open in VS Code
Open the project directory in Visual Studio Code:
```bash
git clone https://github.com/mahaboobtech/esp32-smartwatch.git
cd esp32-smartwatch
code .
```

### Step 2: Install the LVGL Preview Extension
1. Open the Extensions view (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>X</kbd>).
2. Search for and install: **`LVGL Live Preview`** (by *themastercoder007*).

### Step 3: Launch the Simulator
1. Open [`main/app_main.c`](file:///d:/projects/esp32_projects/smartwatch/main/app_main.c).
2. Press <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>L</kbd> (or open Command Palette with <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd> and run `LVGL: Start Live Preview`).
3. The 240×240 smartwatch simulator will open with full mouse/touch navigation, animations, and live code hot-reloading!

---

## 🛠️ Requirements & Setup

### 1. For PC Simulation (Stage 1)
* **Code Editor:** [Visual Studio Code](https://code.visualstudio.com/)
* **VS Code Extensions:**
  * **LVGL Live Preview** (`themastercoder007.lvgl-live-preview`) – compiles your C code to WebAssembly/SDL2 in real-time.
  * **C/C++** (`ms-vscode.cpptools`) – IntelliSense and code navigation.
  * *(No toolchains or compilers need to be installed manually; the LVGL extension manages its own simulation toolchain!)*

### 2. For Physical ESP32 Hardware (Stage 2)
* **Framework:** [ESP-IDF v5.x or v6.x](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
* **VS Code Extension:** **ESP-IDF Extension** (Espressif Systems)
* **Hardware Components:**
  * **MCU:** ESP32 DevKit V1 (ESP32-WROOM-32)
  * **Display:** 1.54″ Square TFT LCD (240×240, ST7789 SPI driver)
  * **Touch:** Capacitive Touch Panel (CST816S I2C driver)
  * **External LED:** 5mm LED + 220Ω resistor connected to GPIO 26
  * Jumper wires & Breadboard

---

## 🎮 Included Applications & Features

| Application | Description | Themed Features |
|---|---|---|
| 🏠 **Home Launcher** | Main hub with branding & app launcher cards | `mahaboobtech` title, `SPOOKY OS` badge, animated breathing aura pulse |
| ⏱️ **Ghost Timer** | Stopwatch with accurate timekeeping | High-contrast amber display (`MM:SS.ms`), **HAUNT** (Start), **FREEZE** (Pause), and **PURGE** (Reset) |
| 🔮 **Witch Torch** | External LED & blink control | Glowing Jack-o'-Lantern indicator orb, **IGNITE** (Toggle), **FLICKER** (Blink mode), speed adjustment (`-100ms`/`+100ms`) |
| 💀 **Soul Counter** | Digital tally counter with safe bounds | Big digital count display, **`-1 SOUL`**, **`+1 SOUL`**, **`-10`**, **`+10`**, and **`PURGE`** (limits `-9999` to `9999`) |

### ✨ UI & Animation Highlights
* **Halloween Color Palette:** Obsidian black (`#090510`), Crypt violet (`#160D22`), Pumpkin neon orange (`#FF6D00`), Ectoplasm slime green (`#00E676`), and Blood crimson (`#D50000`).
* **Page Slide Animations:** Smooth horizontal screen sliding on entry and exit (`LV_SCREEN_LOAD_ANIM_MOVE_LEFT` / `LV_SCREEN_LOAD_ANIM_MOVE_RIGHT`).
* **Breathing Aura:** Real-time opacity pulsing on launcher cards via `lv_anim_t`.
* **Universal Back Navigation:** Consistent header bar with touch-friendly back button (`<`) on every sub-screen.

---

## 📂 Project Architecture

The codebase cleanly separates **Application Logic (Pure C)** from the **UI Layer (LVGL)** so code is 100% testable and portable:

```
ESP32_SmartWatch/
├── .lvgl-live-preview.json        # PC simulator multi-file build configuration
├── CMakeLists.txt                 # ESP-IDF root CMake file
├── LICENSE                        # MIT License
├── README.md                      # Documentation & Guide
└── main/
    ├── CMakeLists.txt             # Component source registry
    ├── idf_component.yml          # LVGL component dependency
    ├── app_main.h                 # Entry point headers
    ├── app_main.c                 # Simulator & firmware main entry
    │
    ├── applications/              # PURE C LOGIC (NO UI CODE)
    │   ├── stopwatch.h / .c       # Stopwatch state machine & timing
    │   ├── led_control.h / .c     # LED states, blink logic & GPIO callbacks
    │   └── counter.h / .c         # Safe bounded integer counter
    │
    └── ui/                        # LVGL GRAPHICAL USER INTERFACE
        ├── ui_manager.h / .c      # Navigation, Halloween themes, & screen transitions
        ├── ui_home.h / .c         # Home launcher screen & mahaboobtech header
        ├── ui_stopwatch.h / .c    # Ghost Timer UI
        ├── ui_led.h / .c          # Witch Torch UI
        └── ui_counter.h / .c      # Soul Counter UI
```

---

## 👨‍💻 Developer Guide: How to Make Changes

Want to customize the UI or add a new app? It's straightforward:

### 1. Changing Colors & Styles
Open [`main/ui/ui_manager.h`](file:///d:/projects/esp32_projects/smartwatch/main/ui/ui_manager.h) and modify any of the theme definitions:
```c
#define COLOR_HAUNT_BG       lv_color_hex(0x090510) /* Background */
#define COLOR_PUMPKIN_ORANGE lv_color_hex(0xFF6D00) /* Accent 1 */
#define COLOR_GHOST_GREEN    lv_color_hex(0x00E676) /* Accent 2 */
```

### 2. Changing the Branding Name
Open [`main/ui/ui_home.c`](file:///d:/projects/esp32_projects/smartwatch/main/ui/ui_home.c) and edit:
```c
lv_label_set_text(lbl_user, "your_name_here");
```

### 3. Adding a New Application
1. **Logic:** Create your logic file in `main/applications/my_app.c` and `my_app.h`.
2. **UI:** Create `main/ui/ui_my_app.c` and `ui_my_app.h` using `ui_manager_create_screen_base("MY APP", true)`.
3. **Register:**
   - Add `UI_SCREEN_MY_APP` in [`main/ui/ui_manager.h`](file:///d:/projects/esp32_projects/smartwatch/main/ui/ui_manager.h).
   - Add your screen switch case in [`main/ui/ui_manager.c`](file:///d:/projects/esp32_projects/smartwatch/main/ui/ui_manager.c).
   - Add a launcher card in [`main/ui/ui_home.c`](file:///d:/projects/esp32_projects/smartwatch/main/ui/ui_home.c).
   - Register the new `.c` files in `main/CMakeLists.txt` and `.lvgl-live-preview.json`.

---

## 🔌 Hardware GPIO Pinout (ESP32 DevKit V1)

When you are ready to flash to the physical display, connect the pins as follows:

| Function | Pin Name | ESP32 GPIO | Description |
|---|---|---|---|
| **Display SPI** | SCLK | `GPIO 18` | SPI Clock |
| | MOSI | `GPIO 23` | SPI Data |
| | CS | `GPIO 13` | Display Chip Select |
| | DC | `GPIO 27` | Data / Command Control |
| | RST | `GPIO 14` | Display Hardware Reset |
| | BLK | `GPIO 25` | Backlight Control |
| **Touch I2C** | SDA | `GPIO 21` | I2C Data |
| | SCL | `GPIO 22` | I2C Clock |
| **External LED** | LED | `GPIO 26` | Physical LED with 220Ω resistor |

---

## 🚀 Building & Flashing to ESP32

To build and flash the project onto your ESP32 board using ESP-IDF:

```bash
# 1. Set the target to standard ESP32
idf.py set-target esp32

# 2. Build the firmware
idf.py build

# 3. Flash to ESP32 and open serial monitor (replace COM_PORT with your port, e.g. COM3 or /dev/ttyUSB0)
idf.py -p COM_PORT flash monitor
```

To exit the serial monitor, press <kbd>Ctrl</kbd> + <kbd>]</kbd>.

---

## 📜 License

This project is open-source and licensed under the **[MIT License](LICENSE)**.

```
Copyright (c) 2026 mahaboobtech
```

Feel free to use, modify, and build on top of this project for personal, educational, or commercial smartwatch devices!
