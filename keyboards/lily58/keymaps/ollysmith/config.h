/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define MASTER_LEFT

#define OLED_TIMEOUT 15000
#undef OLED_FONT_H
#define OLED_FONT_H "keyboards/lily58/keymaps/ollysmith/font.c"
#define OLED_FONT_END 223

// Underglow
#undef RGBLED_NUM
#define RGBLED_NUM 12    // Number of LEDs
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 6, 6 }
#define RGBLIGHT_LED_MAP { 5, 4, 3, 2, 1, 0, 6, 7, 8, 9, 10, 11 }
#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 16
#define RGBLIGHT_VAL_STEP 16
#define RGBW
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP

// Trim some stuff to save ROM space.
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
