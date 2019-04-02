#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MEDIA 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MEDIA,
};

#define SS_SCRN LGUI(LSFT(KC_3))       // Screenshot entire screen
#define CP_SCRN LGUI(LCTL(LSFT(KC_3))) // Screenshot and copy entire screen
#define SS_SELN LGUI(LSFT(KC_4))       // Screenshot selection
#define CP_SELN LGUI(LCTL(LSFT(KC_4))) // Screenshot and copy selection

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,          KC_EQL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,          KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,          KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LGUI, KC_LALT, MEDIA,            LOWER,   KC_LCTL,          KC_SPC,  RAISE,            _______,  _______, KC_RSFT, KC_RCTL
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'l
  ),

  [_LOWER] = LAYOUT(
  KC_TILD, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_HOME,          KC_PGUP,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_END ,          KC_PGDN,     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS, \
  _______, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_BSPC,          KC_BSPC,     KC_F12,  _______, _______, KC_MUTE, _______, KC_PIPE, \
  _______, _______,  _______, _______, _______, KC_BSPC,                                KC_BSPC, _______, _______, _______, _______, _______ \

  ),

  [_RAISE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,     _______,             _______,   KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL,  \
  _______, KC_4,    KC_5,  KC_6,   KC_PLUS, _______,  _______,             _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,  _______, \
  KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, _______,  _______,             _______,   _______, KC_NUHS, KC_NUBS, _______,  _______, KC_BSLS, \
  _______, KC_COMM, KC_0,  KC_DOT, _______, KC_BSPC,                                  KC_BSPC, _______, _______, _______,  _______, _______ \
  ),

  [_MEDIA] = LAYOUT(
     CP_SCRN, CP_SELN, _______, _______, _______, _______, KC_MUTE,         KC_VOLU,  KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,
     SS_SCRN, SS_SELN, _______, _______, _______, _______, _______,         KC_VOLD,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,          _______, _______,         _______,  _______,          _______, _______, _______, RESET
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _MEDIA);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _MEDIA);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _MEDIA);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _MEDIA);
      }
      return false;
      break;
    case MEDIA:
      if (record->event.pressed) {
        layer_on(_MEDIA);
      } else {
        layer_off(_MEDIA);
      }
      return false;
      break;
  }
  return true;
}
