#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define CTL_ESC LCTL_T(KC_ESC)
#define MO_LOW  MO(_LOWER)
#define MO_RAI  MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_LBRC, KC_RBRC, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                               KC_LGUI, KC_LALT, MO_LOW, KC_SPC,  KC_ENT,  MO_RAI, KC_MINS, KC_EQL \
  ),
  [_LOWER] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______, _______, _______, _______\
  ),
  [_RAISE] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______, _______, _______, _______\
  ),
  [_ADJUST] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,  \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______, _______, _______, _______\
  )
};

const rgblight_segment_t PROGMEM my_lower_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_GREEN});
const rgblight_segment_t PROGMEM my_raise_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_BLUE});
const rgblight_segment_t PROGMEM my_adjust_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_RED});
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_lower_rgb_layer, my_raise_rgb_layer, my_adjust_rgb_layer);

void keyboard_post_init_user(void) {
  // Enable the LED layers
  rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
  return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

const char *read_logo(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

const char *read_logo(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_ln("\x9d\x9e\x9f \xdd\xde\xdf \xd9\xdd\xdf \xdd\xd7\xd6 \xdd\xde\xdf", false);
    oled_write_ln("\xbd\x20\x20 \xda\x20\xdc \xda\xdc\xd8 \xda\x20\x20 \xda\xdc\xd8", false);
    oled_write_ln("\xdd\xd7\xdf \xdd\xdf\xd9 \xd5\xde\xd6 \xd9\xdd\xdf \xdd\xde\xdf", false);
    oled_write_ln("\xda\xd7\xdc \xd8\xda\xdc \xd5\xdc\x20 \xda\xdb\xdc \xda\xdb\xdc", false);
  } else {
    oled_write(read_logo(), false);
  }
}

void suspend_power_down_user(void) {
  oled_off();
}
#endif // OLED_DRIVER_ENABLE
