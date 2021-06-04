#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define MY_QWERTY_MAP LAYOUT( \
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                   KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                   KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                   KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC, KC_RBRC, KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                        KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC,  KC_ENT,  MO(_RAISE), KC_MINS, KC_EQL \
)

// Note: LOWER and RAISE currently use the same map.
#define MY_LOWER_RAISE_MAP LAYOUT( \
  KC_ESC,  _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
  _______, _______, _______, _______, _______, _______, LGUI(KC_PSCR), LGUI(KC_PAUSE), KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, _______, \
                             _______, _______, _______, _______,       _______,        _______, _______, _______\
)

#define MY_ADJUST_MAP LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX, \
  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, SGUI(KC_PAUSE), _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______,        _______, _______, _______\
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = MY_QWERTY_MAP,
  [_LOWER] = MY_LOWER_RAISE_MAP,
  [_RAISE] = MY_LOWER_RAISE_MAP,
  [_ADJUST] = MY_ADJUST_MAP
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

void render_bongo_cat(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

const char lut[] = "0123456789ABCDEF";

void render_hex_char(uint8_t num) {
  oled_write_char(lut[num >> 4], false);
  oled_write_char(lut[num & 0xf], false);
}

void render_slider(char label, uint8_t num) {
  uint8_t pos = num >> 4;
  oled_write_char(label, false);
  for (uint8_t i = 0; i < 16 ; i++) {
    oled_write_char(i == pos ? '|' : '-', false);
  }
  render_hex_char(num);
  oled_write_ln("", false);
}

void oled_task_user(void) {
  if (is_keyboard_master() && IS_LAYER_ON(_ADJUST)) {
    oled_write("RGB Mode 0x", false);
    render_hex_char(rgblight_get_mode());
    oled_write_ln("", false);
    render_slider('H', rgblight_get_hue());
    render_slider('S', rgblight_get_sat());
    render_slider('V', rgblight_get_val());
  } else {
    render_bongo_cat();
  }
}

void suspend_power_down_user(void) {
  oled_off();
}
#endif // OLED_DRIVER_ENABLE
