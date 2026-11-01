
# ESP32 Smartwatch – Touchscreen UI & Firmware Project

## 1. Project Overview

This project aims to develop a mini smartwatch-style touchscreen interface using an ESP32 development board.

The interface will have a square display with a home screen, an application launcher, and individual applications. Users will interact with the interface using touch input.

The project will initially be developed and tested on a Windows PC using an LVGL simulator. Once the UI and application logic are working correctly, the project will be deployed to the physical ESP32 board with a touchscreen display.

The firmware will be developed using:

- ESP-IDF
- C programming language
- FreeRTOS
- LVGL graphics library
- Visual Studio Code

The main objective is to develop a clean, modular, responsive, and expandable embedded smartwatch interface.

---

## 2. Hardware Platform

### Main Controller

Board: ESP32 DevKit V1

Controller: ESP32-WROOM-32 (classic ESP32)

ESP-IDF target:

    esp32

The existing ESP32 development board will be used for firmware development and hardware testing.

### Planned Display

Display type: Square TFT touchscreen

Proposed specifications:

- Display size: 1.54 inch
- Resolution: 240 × 240 pixels
- Display controller: ST7789
- Communication: SPI
- Touch controller: CST816S or compatible
- Touch communication: I2C

Important:
The display module must include touchscreen functionality. A normal ST7789 display does not automatically provide touch input.

The exact display module and pinout will be confirmed before purchasing the hardware.

### Provisional GPIO Configuration

These pins are only a proposed configuration. They must be checked against the selected display module and ESP32 board.

| Function | ESP32 GPIO |
|---|---|
| SPI Clock (SCLK) | GPIO18 |
| SPI MOSI | GPIO23 |
| SPI MISO | GPIO19 |
| Display CS | GPIO13 |
| Display DC | GPIO27 |
| Display Reset | GPIO14 |
| Display Backlight | GPIO25 |
| Touch SDA | GPIO21 |
| Touch SCL | GPIO22 |
| External LED | GPIO26 |

---

## 3. Software and Development Environment

### Main Development Tools

| Software | Purpose |
|---|---|
| Visual Studio Code | Main development environment |
| ESP-IDF | ESP32 firmware development framework |
| C | Firmware programming language |
| CMake | Project build configuration |
| FreeRTOS | Task and resource management |
| LVGL | Graphical user interface |
| LVGL Live Preview | PC-based UI simulation |
| Git | Source code version control |

### VS Code Extensions

Required or useful extensions:

1. ESP-IDF Extension – Espressif Systems
2. LVGL Live Preview – themastercoder007
3. C/C++ – Microsoft
4. CMake Tools – Microsoft (optional for general CMake workflows)

The LVGL Live Preview extension will be used to develop and test the UI on the PC before connecting the physical display.

Note:
The LVGL Live Preview extension has its own simulation toolchain. It does not require the ESP32 board to run a UI preview.

---

## 4. Development Strategy

Development will be divided into two stages.

### Stage 1 – PC-Based UI Development

The first stage will focus on developing the graphical interface without physical hardware.

Objectives:

- Create the smartwatch home screen.
- Create the application launcher.
- Design individual application screens.
- Implement buttons and touch interactions.
- Test navigation between screens.
- Test stopwatch functionality.
- Test LED control UI.
- Test digital counter functionality.
- Adjust screen dimensions and layout.
- Test the interface at 240 × 240 resolution.

The LVGL Live Preview extension will be used for this stage.

The simulator will use mouse interaction to test buttons and other touch controls.

Once its dependencies have been downloaded, the preview can be used offline.

### Stage 2 – ESP32 Hardware Development

After the PC simulation is working:

- Configure ESP32 DevKit V1 using ESP-IDF.
- Integrate LVGL into the ESP-IDF project.
- Configure the ST7789 display driver.
- Configure the touchscreen driver.
- Connect the display and touch controller.
- Map touch coordinates to LVGL input.
- Integrate application logic with actual hardware.
- Test the complete interface on the physical display.

The UI and application logic should be reused as much as possible between simulation and hardware.

---

## 5. Project Applications

The smartwatch will initially contain three applications.

### Application 1 – Stopwatch

Purpose:
Measure elapsed time.

Features:

- Start
- Stop / Pause
- Resume
- Reset
- Display elapsed time
- Display minutes, seconds, and milliseconds

The stopwatch should maintain accurate elapsed time.

For ESP32 hardware, the implementation will use the ESP timer facilities rather than relying on repeated UI refresh delays for timekeeping.

### Application 2 – LED Control

Purpose:
Control an external LED using the smartwatch interface.

Features:

- LED ON
- LED OFF
- Toggle
- Blink mode
- Adjustable blinking interval
- Display current LED status

During PC simulation, the LED status will be represented visually on the screen.

During hardware testing, the application will control an actual ESP32 GPIO.

### Application 3 – Digital Counter

Purpose:
Implement a configurable digital counter.

Features:

- Increment
- Decrement
- Reset
- Set custom value
- Display current count
- Prevent unwanted counter overflow or underflow

The counter should update immediately when the user interacts with the interface.

---

## 6. User Interface Design

The display will use a square 240 × 240 layout.

The UI should have a modern smartwatch appearance.

### Home Screen

The home screen will contain:

- Smartwatch title or clock area
- Application launcher
- Stopwatch icon
- LED control icon
- Counter icon
- Clean background
- Consistent spacing and alignment

### Application Navigation

The user should be able to:

1. Open the home screen.
2. Select an application.
3. Enter the selected application.
4. Interact with its controls.
5. Return to the home screen.

Each application should have its own screen and independent functionality.

### UI Design Guidelines

- Use a dark modern theme.
- Use readable text and icons.
- Avoid overcrowding the small display.
- Use consistent button dimensions.
- Keep touch targets large enough.
- Provide visual feedback when buttons are pressed.
- Keep navigation simple.
- Design for a 240 × 240 resolution.
- Use reusable UI components wherever possible.

---

## 7. Software Architecture

The firmware will follow a modular architecture.

The project will separate:

1. Hardware drivers
2. User interface
3. Application logic
4. RTOS task management
5. System initialization

### UI Layer

Responsible for:

- Home screen
- Application launcher
- Stopwatch screen
- LED screen
- Counter screen
- Navigation
- Button events
- UI updates

### Application Layer

Responsible for:

- Stopwatch calculations
- LED control logic
- Counter operations
- Application state

### Hardware Layer

Responsible for:

- Display initialization
- Touchscreen initialization
- GPIO configuration
- SPI communication
- I2C communication

### System Layer

Responsible for:

- FreeRTOS task management
- Shared resource management
- Communication between tasks
- System initialization

---

## 8. FreeRTOS Architecture

FreeRTOS will be used for firmware task management.

The initial architecture will keep LVGL operations in a dedicated UI task.

Other tasks should communicate with the UI through queues, notifications, or other controlled mechanisms instead of directly modifying LVGL objects.

Planned responsibilities:

| Task | Responsibility |
|---|---|
| UI Task | LVGL handling and screen updates |
| Application Task | Application logic |
| Hardware Task | Hardware operations when needed |
| System Task | System monitoring and background operations |

The final number of tasks will depend on actual application requirements.

Important considerations:

- Avoid multiple tasks accessing LVGL simultaneously.
- Use queues or task notifications for communication.
- Use mutexes only when shared resources require protection.
- Avoid unnecessary blocking inside the UI task.
- Use appropriate task priorities.
- Use watchdog-compatible task design.

---

## 9. Initial Project Folder Structure

The project will use the following modular structure.

    ESP32_SmartWatch/
    |
    |-- main/
    |   |
    |   |-- CMakeLists.txt
    |   |-- app_main.c
    |   |-- app_main.h
    |   |
    |   |-- ui/
    |   |   |
    |   |   |-- ui_manager.c
    |   |   |-- ui_manager.h
    |   |   |-- ui_home.c
    |   |   |-- ui_home.h
    |   |   |-- ui_stopwatch.c
    |   |   |-- ui_stopwatch.h
    |   |   |-- ui_led.c
    |   |   |-- ui_led.h
    |   |   |-- ui_counter.c
    |   |   |-- ui_counter.h
    |   |
    |   |-- applications/
    |   |   |
    |   |   |-- stopwatch.c
    |   |   |-- stopwatch.h
    |   |   |-- led_control.c
    |   |   |-- led_control.h
    |   |   |-- counter.c
    |   |   |-- counter.h
    |   |
    |   |-- display/
    |   |   |
    |   |   |-- display_init.c
    |   |   |-- display_init.h
    |   |
    |   |-- touch/
    |   |   |
    |   |   |-- touch_init.c
    |   |   |-- touch_init.h
    |   |
    |   |-- system/
    |       |
    |       |-- task_manager.c
    |       |-- task_manager.h
    |
    |-- components/
    |   |
    |   |-- lvgl/
    |   |-- display_driver/
    |   |-- touch_driver/
    |
    |-- CMakeLists.txt
    |-- sdkconfig
    |-- README.md

This is the planned final architecture. Files will be added progressively as their functionality is implemented.

---

## 10. ESP-IDF Project Configuration

The root CMakeLists.txt will contain:

    cmake_minimum_required(VERSION 3.16)

    include($ENV{IDF_PATH}/tools/cmake/project.cmake)

    project(ESP32_SmartWatch)

The main/CMakeLists.txt will register the source files:

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

Additional source files and component dependencies will be registered as the project develops.

LVGL and display/touch drivers will later be added as ESP-IDF components.

### ESP32 Target Configuration

The board target is:

    esp32

To configure the project:

    idf.py set-target esp32

To open the configuration menu:

    idf.py menuconfig

To build:

    idf.py build

To flash:

    idf.py flash

To monitor serial output:

    idf.py monitor

To build, flash, and monitor:

    idf.py build flash monitor

These commands require a correctly installed ESP-IDF environment and a connected ESP32 board for flashing.

---

## 11. LVGL Live Preview Setup

The PC simulator will be used before hardware development.

### Initial Setup

1. Open the project folder in VS Code.
2. Install the LVGL Live Preview extension.
3. Open the VS Code command palette using Ctrl + Shift + P.
4. Execute:

       LVGL: Check Setup

5. Allow the extension to install its required simulation dependencies.
6. Open or create an LVGL C source file.
7. Add the required preview entry point:

       #ifdef LVGL_LIVE_PREVIEW
       void lvgl_live_preview_init(void)
       {
           // Initialize the smartwatch UI here.
       }
       #endif

8. Start the preview using:

       LVGL: Start Live Preview

   Or use Ctrl + Shift + L.

9. Configure the preview resolution to 240 × 240.
10. Test the interface using the mouse.

The extension uses its own preview build environment. The preview entry point is not the ESP-IDF application entry point.

### LVGL Version

Use LVGL 9.x for the initial UI implementation.

The UI code should consistently use the selected LVGL version.

---

## 12. Coding Standards

The project should follow these principles:

- Use C for firmware development.
- Keep UI code separate from application logic.
- Use meaningful function and variable names.
- Use header files for public function declarations.
- Keep functions small and focused.
- Avoid unnecessary global variables.
- Use appropriate data types.
- Handle counter limits safely.
- Keep timing logic independent of UI refresh rates.
- Avoid blocking delays in the UI task.
- Add comments where logic is not obvious.
- Keep hardware-specific code separate from the UI.

---

## 13. Development Roadmap

### Phase 1 – Development Environment

- [ ] Install ESP-IDF extension.
- [ ] Verify ESP-IDF installation.
- [ ] Install LVGL Live Preview.
- [ ] Configure the project folder.
- [ ] Configure ESP32 target.
- [ ] Verify PC simulator.

### Phase 2 – UI Development

- [ ] Create smartwatch home screen.
- [ ] Design application launcher.
- [ ] Implement navigation.
- [ ] Create stopwatch screen.
- [ ] Create LED control screen.
- [ ] Create counter screen.
- [ ] Implement button interactions.
- [ ] Test all screens in the PC simulator.

### Phase 3 – Application Logic

- [ ] Implement stopwatch logic.
- [ ] Implement LED control logic.
- [ ] Implement digital counter logic.
- [ ] Integrate application logic with UI.
- [ ] Test application state and updates.

### Phase 4 – ESP32 Integration

- [ ] Configure ESP32 DevKit V1.
- [ ] Integrate LVGL into ESP-IDF.
- [ ] Configure display driver.
- [ ] Configure touch driver.
- [ ] Configure GPIO.
- [ ] Test display output.
- [ ] Test touchscreen input.

### Phase 5 – FreeRTOS Integration

- [ ] Create UI task.
- [ ] Configure application task architecture.
- [ ] Implement task communication.
- [ ] Protect shared resources.
- [ ] Verify system stability.

### Phase 6 – Final Testing

- [ ] Test home screen.
- [ ] Test application navigation.
- [ ] Test stopwatch accuracy.
- [ ] Test LED ON/OFF.
- [ ] Test LED blinking.
- [ ] Test counter operations.
- [ ] Test touchscreen response.
- [ ] Test long-duration operation.
- [ ] Optimize memory and performance.

---

## 14. Important Development Rules

1. Develop and test the UI on the PC first.
2. Do not purchase the display until the UI layout is reasonably finalized.
3. Keep the UI independent of the physical display hardware.
4. Keep application logic independent of LVGL wherever possible.
5. Use the ESP32 DevKit V1 as the initial hardware target.
6. Use LVGL 9.x consistently.
7. Do not create all implementation files before they are required.
8. Implement and test one application at a time.
9. Maintain a working project at every development stage.
10. Integrate physical hardware only after the PC-based UI and application logic are stable.

---

## 15. Current Project Status

Current development stage: Initial project setup.

Existing hardware:
- ESP32 DevKit V1.

Display:
- Not purchased yet.

Development computer:
- Windows PC.
- Visual Studio Code.

Simulation:
- LVGL Live Preview extension installed.

Initial UI resolution:
- 240 × 240 pixels.

Planned applications:
- Stopwatch.
- LED Control.
- Digital Counter.

Current priority:
Set up the project structure and verify the LVGL PC simulator before developing the complete smartwatch UI.

---

## 16. Main Project Goal

Develop a complete mini smartwatch interface using ESP32, LVGL, and FreeRTOS.

The final device should provide a responsive touchscreen UI, independent applications, reliable application logic, and a modular firmware architecture.

The development process will start with PC simulation and progress toward a working ESP32 touchscreen device.
