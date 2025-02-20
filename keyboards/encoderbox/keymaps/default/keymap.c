// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(JS_0, JS_1, JS_2, JS_3, JS_4, JS_5, JS_6, JS_7)
};

// #if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(JS_8, JS_9),
        ENCODER_CCW_CW(JS_10, JS_11),
        ENCODER_CCW_CW(JS_12, JS_13),
        ENCODER_CCW_CW(JS_14, JS_15)
    },
};
//#endif
