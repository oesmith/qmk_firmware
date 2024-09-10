// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
  LY0 = 0,
  LY1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │ M │ N │ O │ P │ Q │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [LY0] = LAYOUT(
        // TODO: Get the joystick device working (last four keys of first row).
        KC_UP,   KC_DOWN, KC_LEFT, KC_RGHT, JS_0,    JS_1,    JS_2,    JS_3,
        KC_LSFT, KC_RSFT, KC_LCTL, KC_RCTL, KC_LALT, MS_BTN1, KC_RALT, MS_BTN2,
        MS_BTN3, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,

        JS_4,    JS_5,    KC_VOLU, KC_GRV,  KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_ESC,  KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,
        KC_O,    KC_P,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,
        KC_J,    KC_K,    KC_L,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, KC_SCLN, KC_QUOT,
        KC_BSPC, KC_ENT,  MO(LY1), MO(LY1), KC_SPC,  KC_NO,   KC_NO,   KC_NO
    ),

    [LY1] = LAYOUT(
        KC_PGUP, KC_PGDN, KC_HOME, KC_END,  _______, _______, _______, _______,
        _______, _______, _______, _______, KC_LGUI, _______, KC_RGUI, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,

        KC_PSCR, KC_PAUS, KC_VOLD, _______, _______, _______, KC_F11,  KC_F12,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  QK_BOOT, KC_CAPS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_PGUP, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        KC_END,  KC_PGDN, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_BRID, KC_BRIU, _______, _______, _______, _______,
        KC_DEL,  _______, _______, _______, BL_STEP, _______, _______, _______
    ),
};
