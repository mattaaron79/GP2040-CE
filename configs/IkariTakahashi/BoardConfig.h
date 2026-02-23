/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef IKARI_TAKAHASHI_CONFIG_H_
#define IKARI_TAKAHASHI_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "Ikari: takahashi_1b"

// Board config for HE prototype

// Left Side
// Pin to physical button mappings. Used to represent the physical button pressed on the display layout instead of the mapped (logical) button
//|7|[1][2][3]
//| |[4][5][6]
//
//       [ 8 ]

// [9] [10] (Small PCB Buttons)
// [11] Lock
// [12] Function

// Virtual Pins
#define VPIN_COUNT 32

// Virtual Pin GPIO Mappings
// #define VPIN_GPIO_0 22
// #define VPIN_GPIO_1 23
// #define VPIN_GPIO_2 24
// #define VPIN_GPIO_3 19
// #define VPIN_GPIO_4 20
// #define VPIN_GPIO_5 21
// #define VPIN_GPIO_6 25
// #define VPIN_GPIO_7 18
// #define VPIN_GPIO_8 7
// #define VPIN_GPIO_9 6
// #define VPIN_GPIO_10 4

// Virtual Pin Analog Channel Mappings
// #define VPIN_ANALOG_00 3
// #define VPIN_ANALOG_01 0
// #define VPIN_ANALOG_02 1
// #define VPIN_ANALOG_03 5
// #define VPIN_ANALOG_04 7
// #define VPIN_ANALOG_05 6
// #define VPIN_ANALOG_06 4
// #define VPIN_ANALOG_07 2

// Virtual Pin LED Mappings
// #define VPIN_LED_1 0
// #define VPIN_LED_2 1
// #define VPIN_LED_3 2
// #define VPIN_LED_4 3
// #define VPIN_LED_5 4
// #define VPIN_LED_6 5
// #define VPIN_LED_7 6
// #define VPIN_LED_8 7



#define ANALOG_ACTUATE_DEFAULT 0.15f

// #define ANALOG_TRIGGER_OPTIONS_
// #define ANALOG_TRIGGER_ENABLED true
// #define ANALOG_TRIGGER_MUX_CHANNELS 8
// #define ANALOG_TRIGGER_SELECT_PIN_0 13
// #define ANALOG_TRIGGER_SELECT_PIN_1 14
// #define ANALOG_TRIGGER_SELECT_PIN_2 15
// #define ANALOG_TRIGGER_SELECT_PIN_3 -1
// #define ANALOG_TRIGGER_MUX_ADC_PIN_0 26
// #define ANALOG_TRIGGER_MUX_ADC_PIN_1 -1
// #define ANALOG_TRIGGER_MUX_ADC_PIN_2 -1
// #define ANALOG_TRIGGER_MUX_ADC_PIN_3 -1
// #define ANALOG_TRIGGER_EMA_SMOOTHING false
// #define ANALOG_TRIGGER_SMOOTHING_FACTOR 1
// #define ANALOG_TRIGGER_RAPID_TRIGGER true
// #define ANALOG_TRIGGER_ACTUATE ANALOG_ACTUATE_DEFAULT
// #define ANALOG_TRIGGER_RELEASE ANALOG_ACTUATE_DEFAULT

#define GPIO_PIN_05 GpioAction::BUTTON_PRESS_S2
#define GPIO_PIN_22 GpioAction::VPIN_00
#define GPIO_PIN_23 GpioAction::VPIN_01
#define GPIO_PIN_24 GpioAction::VPIN_02
#define GPIO_PIN_19 GpioAction::VPIN_03
#define GPIO_PIN_20 GpioAction::VPIN_04
#define GPIO_PIN_21 GpioAction::VPIN_05
#define GPIO_PIN_25 GpioAction::VPIN_06
#define GPIO_PIN_18 GpioAction::VPIN_07
#define GPIO_PIN_07 GpioAction::VPIN_08
#define GPIO_PIN_06 GpioAction::VPIN_09
#define GPIO_PIN_04 GpioAction::VPIN_10
// #define GPIO_PIN_05 GpioAction::VPIN_12

// Virtual Pin Action Mappings
#define GPIO_VPIN_00 GpioAction::BUTTON_PRESS_L2
#define GPIO_VPIN_01 GpioAction::BUTTON_PRESS_UP
#define GPIO_VPIN_02 GpioAction::BUTTON_PRESS_L2
#define GPIO_VPIN_03 GpioAction::BUTTON_PRESS_LEFT
#define GPIO_VPIN_04 GpioAction::BUTTON_PRESS_DOWN
#define GPIO_VPIN_05 GpioAction::BUTTON_PRESS_RIGHT
#define GPIO_VPIN_06 GpioAction::BUTTON_PRESS_L3
#define GPIO_VPIN_07 GpioAction::BUTTON_PRESS_L2
#define GPIO_VPIN_08 GpioAction::BUTTON_PRESS_S1
#define GPIO_VPIN_09 GpioAction::BUTTON_PRESS_S2

// Shaberi
#define PIN_UART1_RX 9
#define PIN_UART1_TX 8

// Setting GPIO pins to assigned by add-on
//
// #define GPIO_PIN_01 GpioAction::ASSIGNED_TO_ADDON
// #define GPIO_PIN_02 GpioAction::ASSIGNED_TO_ADDON
// #define GPIO_PIN_03 GpioAction::ASSIGNED_TO_ADDON
// #define GPIO_PIN_04 GpioAction::ASSIGNED_TO_ADDON
// #define GPIO_PIN_05 GpioAction::ASSIGNED_TO_ADDON

// Keyboard Mapping Configuration
//                                            // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define KEY_DPAD_UP HID_KEY_ARROW_UP       // UP     | UP     | UP      | UP       | UP     | UP     |
#define KEY_DPAD_DOWN HID_KEY_ARROW_DOWN   // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define KEY_DPAD_RIGHT HID_KEY_ARROW_RIGHT // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define KEY_DPAD_LEFT HID_KEY_ARROW_LEFT   // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |
#define KEY_BUTTON_B1 HID_KEY_SHIFT_LEFT   // B1     | A      | B       | Cross    | 2      | K1     |
#define KEY_BUTTON_B2 HID_KEY_Z            // B2     | B      | A       | Circle   | 3      | K2     |
#define KEY_BUTTON_R2 HID_KEY_X            // R2     | RT     | ZR      | R2       | 8      | K3     |
#define KEY_BUTTON_L2 HID_KEY_V            // L2     | LT     | ZL      | L2       | 7      | K4     |
#define KEY_BUTTON_B3 HID_KEY_CONTROL_LEFT // B3     | X      | Y       | Square   | 1      | P1     |
#define KEY_BUTTON_B4 HID_KEY_ALT_LEFT     // B4     | Y      | X       | Triangle | 4      | P2     |
#define KEY_BUTTON_R1 HID_KEY_SPACE        // R1     | RB     | R       | R1       | 6      | P3     |
#define KEY_BUTTON_L1 HID_KEY_C            // L1     | LB     | L       | L1       | 5      | P4     |
#define KEY_BUTTON_S1 HID_KEY_5            // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define KEY_BUTTON_S2 HID_KEY_1            // S2     | Start  | Plus    | Start    | 10     | Start  |
#define KEY_BUTTON_L3 HID_KEY_EQUAL        // L3     | LS     | LS      | L3       | 11     | LS     |
#define KEY_BUTTON_R3 HID_KEY_MINUS        // R3     | RS     | RS      | R3       | 12     | RS     |
#define KEY_BUTTON_A1 HID_KEY_9            // A1     | Guide  | Home    | PS       | 13     | ~      |
#define KEY_BUTTON_A2 HID_KEY_F2           // A2     | ~      | Capture | ~        | 14     | ~      |
#define KEY_BUTTON_FN -1                   // Hotkey Function                                        |

#define USB_PERIPHERAL_ENABLED 0
#define USB_PERIPHERAL_PIN_DPLUS 1

#define DEFAULT_INPUT_MODE_R1 INPUT_MODE_XBONE
#define DEFAULT_INPUT_MODE_B4 INPUT_MODE_PS5
#define DEFAULT_PS5AUTHENTICATION_TYPE INPUT_MODE_AUTH_TYPE_USB

#define BOARD_LEDS_PIN 0

#define LED_BRIGHTNESS_MAXIMUM 50
#define LEDS_PER_PIXEL 1
#define LEDS_BASE_ANIMATION_INDEX 1

// Pin to LED order mapping
#define LEDS_PIN_

#define HAS_I2C_DISPLAY 1
#define I2C1_ENABLED 1
#define I2C1_PIN_SDA 10
#define I2C1_PIN_SCL 11
// #define I2C_BLOCK i2c1
#define I2C1_SPEED 100000
#define DISPLAY_SIZE GPGFX_DisplaySize::SIZE_128x32
#define DISPLAY_FLIP 1
#define DISPLAY_INVERT 0
#define DISPLAY_SAVER_TIMEOUT 0

#define REVERSE_UP_DEFAULT 1
#define REVERSE_DOWN_DEFAULT 1
#define REVERSE_LEFT_DEFAULT 1
#define REVERSE_RIGHT_DEFAULT 1

#define SPLASH_MODE SPLASH_MODE_STATIC
#define SPLASH_DURATION 3000

#define BUTTON_LAYOUT BUTTON_LAYOUT_BOARD_DEFINED_A
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_BOARD_DEFINED_B

// // KeebBrawler-04MX rev3
// #define DEFAULT_BOARD_LAYOUT_A {                                             \
//     {GP_ELEMENT_PIN_BUTTON, {5, 20, 12, 36, 1, 1, 6, GP_SHAPE_PILL}},        \
//     {GP_ELEMENT_PIN_BUTTON, {19, 23, 4, 4, 1, 1, 7, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {29, 23, 4, 4, 1, 1, 8, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {38, 26, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}},     \
//     {GP_ELEMENT_PIN_BUTTON, {31, 50, 38, 43, 1, 1, 19, GP_SHAPE_PILL, 135}}, \
//     {GP_ELEMENT_PIN_BUTTON, {42, 50, 49, 43, 1, 1, 11, GP_SHAPE_PILL, 135}}, \
//     {GP_ELEMENT_PIN_BUTTON, {31, 14, 4, 4, 1, 1, 28, GP_SHAPE_ELLIPSE}},     \
// }

// #define DEFAULT_BOARD_LAYOUT_B {                                            \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {99, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {109, 19, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {87, 32, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {98, 30, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {108, 30, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {86, 50, 93, 43, 1, 1, 9, GP_SHAPE_PILL, 45}},  \
//     {GP_ELEMENT_PIN_BUTTON, {76, 50, 83, 43, 1, 1, 20, GP_SHAPE_PILL, 45}}, \
//     {GP_ELEMENT_PIN_BUTTON, {116, 17, 123, 33, 1, 1, 13, GP_SHAPE_PILL}},   \
// }

// // KeebBrawler-03MX
// #define DEFAULT_BOARD_LAYOUT_A_ALT0 {                                        \
//     {GP_ELEMENT_PIN_BUTTON, {5, 20, 12, 36, 1, 1, 6, GP_SHAPE_PILL}},        \
//     {GP_ELEMENT_PIN_BUTTON, {19, 23, 4, 4, 1, 1, 7, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {29, 23, 4, 4, 1, 1, 8, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {38, 26, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}},     \
//     {GP_ELEMENT_PIN_BUTTON, {31, 50, 38, 43, 1, 1, 19, GP_SHAPE_PILL, 135}}, \
//     {GP_ELEMENT_PIN_BUTTON, {51, 50, 73, 43, 1, 1, 11, GP_SHAPE_PILL}},      \
// }
// #define DEFAULT_BOARD_LAYOUT_B_ALT0 {                                      \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {99, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {109, 19, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {87, 32, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {98, 30, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {108, 30, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {86, 50, 93, 43, 1, 1, 9, GP_SHAPE_PILL, 45}}, \
//     {GP_ELEMENT_PIN_BUTTON, {116, 17, 123, 33, 1, 1, 13, GP_SHAPE_PILL}},  \
// }

// // KeebBrawler-02MX
// #define DEFAULT_BOARD_LAYOUT_A_ALT1 {                                         \
//     {GP_ELEMENT_PIN_BUTTON, {25, 25, 19, 19, 1, 1, 7, GP_SHAPE_SQUARE, 15}},  \
//     {GP_ELEMENT_PIN_BUTTON, {32, 27, 26, 21, 1, 1, 8, GP_SHAPE_SQUARE, 15}},  \
//     {GP_ELEMENT_PIN_BUTTON, {39, 29, 33, 23, 1, 1, 10, GP_SHAPE_SQUARE, 15}}, \
//     {GP_ELEMENT_PIN_BUTTON, {38, 20, 25, 14, 1, 1, 20, GP_SHAPE_SQUARE, 15}}, \
//     {GP_ELEMENT_PIN_BUTTON, {51, 45, 73, 38, 1, 1, 11, GP_SHAPE_PILL}},       \
//     {GP_ELEMENT_PIN_BUTTON, {16, 29, 4, 23, 1, 1, 6, GP_SHAPE_SQUARE, 15}},   \
// }

// #define DEFAULT_BOARD_LAYOUT_B_ALT1 {                                     \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {97, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {106, 19, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {115, 21, 4, 4, 1, 1, 19, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {87, 30, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {97, 28, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {106, 28, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {115, 30, 4, 4, 1, 1, 9, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {89, 39, 4, 4, 1, 1, 13, GP_SHAPE_ELLIPSE}},  \
// }

// // KeebFighter+S3 rev3
// #define DEFAULT_BOARD_LAYOUT_A_ALT2 {                                    \
//     {GP_ELEMENT_PIN_BUTTON, {19, 23, 4, 4, 1, 1, 7, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {29, 23, 4, 4, 1, 1, 8, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {31, 14, 4, 4, 1, 1, 28, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {39, 25, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {45, 46, 6, 6, 1, 1, 11, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {9, 27, 5, 5, 1, 1, 6, GP_SHAPE_ELLIPSE}},   \
// }

// #define DEFAULT_BOARD_LAYOUT_B_ALT2 {                                     \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {97, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {106, 20, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {115, 22, 4, 4, 1, 1, 19, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {87, 30, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {96, 28, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {105, 29, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {114, 31, 4, 4, 1, 1, 9, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {81, 46, 6, 6, 1, 1, 20, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {93, 41, 4, 4, 1, 1, 13, GP_SHAPE_ELLIPSE}},  \
// }

// // KeebFighter+S4 rev3
// #define DEFAULT_BOARD_LAYOUT_A_ALT3 {                                    \
//     {GP_ELEMENT_PIN_BUTTON, {9, 28, 6, 6, 1, 1, 6, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {19, 23, 4, 4, 1, 1, 7, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {29, 23, 4, 4, 1, 1, 8, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {38, 27, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {37, 42, 4, 4, 1, 1, 19, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {49, 46, 6, 6, 1, 1, 11, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {31, 14, 4, 4, 1, 1, 28, GP_SHAPE_ELLIPSE}}, \
// }

// #define DEFAULT_BOARD_LAYOUT_B_ALT3 {                                     \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {97, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {106, 19, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {88, 30, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {97, 28, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {106, 28, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}}, \
//     {GP_ELEMENT_PIN_BUTTON, {92, 42, 4, 4, 1, 1, 9, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {80, 46, 6, 6, 1, 1, 20, GP_SHAPE_ELLIPSE}},  \
//     {GP_ELEMENT_PIN_BUTTON, {116, 23, 6, 6, 1, 1, 13, GP_SHAPE_ELLIPSE}}, \
// }

// // KeebBrawler-05 rev3
// #define DEFAULT_BOARD_LAYOUT_A_ALT4 {                                        \
//     {GP_ELEMENT_PIN_BUTTON, {5, 20, 12, 36, 1, 1, 28, GP_SHAPE_PILL}},       \
//     {GP_ELEMENT_PIN_BUTTON, {19, 23, 4, 4, 1, 1, 7, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {29, 23, 4, 4, 1, 1, 8, GP_SHAPE_ELLIPSE}},      \
//     {GP_ELEMENT_PIN_BUTTON, {38, 26, 4, 4, 1, 1, 10, GP_SHAPE_ELLIPSE}},     \
//     {GP_ELEMENT_PIN_BUTTON, {31, 50, 38, 43, 1, 1, 6, GP_SHAPE_PILL, 135}},  \
//     {GP_ELEMENT_PIN_BUTTON, {42, 50, 49, 43, 1, 1, 11, GP_SHAPE_PILL, 135}}, \
//     {GP_ELEMENT_PIN_BUTTON, {115, 21, 4, 4, 1, 1, 19, GP_SHAPE_ELLIPSE}},    \
// }

// #define DEFAULT_BOARD_LAYOUT_B_ALT4 {                                       \
//     {GP_ELEMENT_PIN_BUTTON, {88, 21, 4, 4, 1, 1, 16, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {97, 19, 4, 4, 1, 1, 14, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {106, 19, 4, 4, 1, 1, 15, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {87, 30, 4, 4, 1, 1, 12, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {96, 28, 4, 4, 1, 1, 17, GP_SHAPE_ELLIPSE}},    \
//     {GP_ELEMENT_PIN_BUTTON, {105, 28, 4, 4, 1, 1, 18, GP_SHAPE_ELLIPSE}},   \
//     {GP_ELEMENT_PIN_BUTTON, {86, 50, 93, 43, 1, 1, 13, GP_SHAPE_PILL, 45}}, \
//     {GP_ELEMENT_PIN_BUTTON, {76, 50, 83, 43, 1, 1, 20, GP_SHAPE_PILL, 45}}, \
//     {GP_ELEMENT_PIN_BUTTON, {114, 30, 4, 4, 1, 1, 9, GP_SHAPE_ELLIPSE}},    \
// }

#define FOCUS_MODE_ENABLED 1
#define FOCUS_MODE_BUTTON_MASK GAMEPAD_MASK_S1 | GAMEPAD_MASK_S2 | GAMEPAD_MASK_A1 | GAMEPAD_MASK_A2
#define FOCUS_MODE_BUTTON_LOCK_ENABLED 1

#define DEFAULT_SPLASH                                                                                \
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x04, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x3C, 0x33, 0x80, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x18, 0xB3, 0xE0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x60, 0x07, 0x9F, 0xF0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x44, 0x06, 0x3F, 0xF0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x40, 0x0F, 0x80, 0x0F, 0xE0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x40, 0x98, 0x00, 0x0C, 0xF8, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0xCE, 0x00, 0x00, 0x1F, 0xF0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0xFE, 0x00, 0x00, 0x3F, 0xF0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x01, 0xC1, 0x00, 0x00, 0x3F, 0xF0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xE0, 0x87, 0x00, 0x40, 0x00, 0x3F, 0xA0, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x0C, 0x00, 0x20, 0x00, 0x07, 0x80, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xEC, 0x90, 0x3C, 0x06, 0x00, 0x01, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0xE1, 0xBC, 0x03, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x20, 0x02, 0x00, 0x30, 0x00, 0x03, 0xC0, 0x00, 0x3F, 0xF0, 0x00, 0x04, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x30, 0x00, 0x03, 0xC0, 0x00, 0x3F, 0xFC, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x60, 0x00, 0x03, 0x60, 0x00, 0x30, 0x0E, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x60, 0x00, 0x03, 0x60, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x40, 0x00, 0x02, 0x60, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0xC0, 0x00, 0x06, 0x20, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0xC0, 0x00, 0x06, 0x30, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x01, 0x80, 0x00, 0x06, 0x30, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x01, 0x80, 0x00, 0x04, 0x30, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x01, 0x00, 0x00, 0x04, 0x10, 0x00, 0x30, 0x02, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x03, 0x00, 0x00, 0x0C, 0x18, 0x00, 0x30, 0x02, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x03, 0x00, 0x00, 0x0C, 0x18, 0x00, 0x30, 0x02, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x06, 0x00, 0x00, 0x08, 0x18, 0x00, 0x30, 0x02, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x06, 0x00, 0x00, 0x08, 0x08, 0x00, 0x30, 0x02, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x04, 0x00, 0x00, 0x18, 0x0C, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x0C, 0x00, 0x00, 0x18, 0x0C, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x03, 0xFC, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x30, 0x0C, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x03, 0xF8, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x3F, 0xF8, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x0C, 0x00, 0x00, 0x30, 0x04, 0x00, 0x30, 0x18, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x0C, 0x00, 0x00, 0x30, 0x06, 0x00, 0x30, 0x18, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x06, 0x00, 0x00, 0x30, 0x06, 0x00, 0x30, 0x0C, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x03, 0x00, 0x00, 0x20, 0x02, 0x00, 0x30, 0x0C, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x03, 0x00, 0x00, 0x60, 0x03, 0x00, 0x30, 0x06, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x01, 0x80, 0x00, 0x60, 0x03, 0x00, 0x30, 0x03, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x01, 0x80, 0x00, 0x60, 0x03, 0x00, 0x30, 0x03, 0x00, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0xC0, 0x00, 0x40, 0x03, 0x00, 0x30, 0x01, 0x80, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x40, 0x00, 0xC0, 0x01, 0x80, 0x30, 0x01, 0x80, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x60, 0x00, 0xC0, 0x01, 0x80, 0x30, 0x00, 0xC0, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x30, 0x00, 0xC0, 0x01, 0x80, 0x30, 0x00, 0xC0, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x30, 0x00, 0x80, 0x00, 0x80, 0x30, 0x00, 0x60, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x18, 0x00, 0x80, 0x00, 0x80, 0x30, 0x00, 0x20, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x18, 0x01, 0x80, 0x00, 0xC0, 0x30, 0x00, 0x30, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x0C, 0x01, 0x80, 0x00, 0xC0, 0x30, 0x00, 0x18, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x06, 0x01, 0x00, 0x00, 0x40, 0x30, 0x00, 0x18, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x30, 0x02, 0x00, 0x06, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#endif