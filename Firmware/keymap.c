// Copyright 2026 Ethan Wang (@ketchupismm-cell)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Physical top row    (SW1, SW4, SW7)          -> matrix Row 2
// Physical middle row (SW3, SW5, SW6, SW11)     -> matrix Row 1
// Physical bottom row (SW8, SW9, SW10, SW12)    -> matrix Row 0
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_8, KC_9, KC_0, KC_ESC,   // matrix row0 = physical bottom row
        KC_4, KC_5, KC_6, KC_7,     // matrix row1 = physical middle row
        KC_1, KC_2, KC_3            // matrix row2 = physical top row
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

// Encoder push button is wired directly to GP29, not through the matrix,
// so we poll it manually and send a keycode when pressed.
void keyboard_pre_init_user(void) {
    gpio_set_pin_input_high(GP29);
}

static bool encoder_switch_pressed = false;

void matrix_scan_user(void) {
    bool pressed = !gpio_read_pin(GP29); // active low with pull-up
    if (pressed && !encoder_switch_pressed) {
        register_code(KC_MPLY);
    } else if (!pressed && encoder_switch_pressed) {
        unregister_code(KC_MPLY);
    }
    encoder_switch_pressed = pressed;
}
