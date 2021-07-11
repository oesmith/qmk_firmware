/* Copyright 2019 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_number {
  _BASE = 0,
  _LOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    LT(_LOWER, KC_ESCAPE), LGUI(KC_PSCREEN), LGUI(KC_PAUSE), KC_RALT \
  ),
  [_LOWER] = LAYOUT(
    KC_TRNS, KC_TRNS, SGUI(KC_PAUSE), RESET \
  ),
};

void keyboard_post_init_user(void) {
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
}
