/*
 * Keyboard: Atreus
 * Keymap:   replicaJunction
 * Version:  2.2
 */

#include QMK_KEYBOARD_H
#include "replicaJunction.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// These keymaps use "key groups" defined in replicaJunction.h.

// If using a key group, use LAYOUT_wrapper();
// otherwise, use LAYOUT()

[L_COLEMAK] = LAYOUT_wrapper(
  __________________COLEMAK_L1_______________,                   __________________COLEMAK_R1_______________,
  __________________COLEMAK_L2_______________,                   __________________COLEMAK_R2_______________,
  __________________COLEMAK_L3_______________,                   __________________COLEMAK_R3_______________,
  TD_LAYR, KC_LGUI, KC_TAB,  KC_LSFT, KX_BKNM, KX_DCTL, KX_NALT, KX_SPAC, KC_RSFT, KC_MINS, KC_QUOT, KC_EQL
)
,

[L_NUM] = LAYOUT_wrapper(
  _________________L_SYMBOL_1________________,                   __________________L_NUMBER1________________,
  _________________L_SYMBOL_2________________,                   __________________L_NUMBER2________________,
  _________________L_SYMBOL_3________________,                   __________________L_NUMBER3________________,
  _______, KC_AMPR, KC_TILD, KC_GRV,  ooooooo, _______, KC_ENT,  _______, KC_0,    KC_DOT,  KC_EQL,  KC_PLUS
)
,

[L_EXTEND] = LAYOUT_wrapper(
  _________________L_EXTEND_L1_______________,                    _________________L_EXTEND_R1_______________,
  _________________L_EXTEND_L2_______________,                    _________________L_EXTEND_R2_______________,
  _________________L_EXTEND_L3_______________,                    _________________L_EXTEND_R3_______________,
  _______, _______, _______, _______, _______,  KC_DEL,  KC_ENT,  ooooooo, _______, _______, _______, KC_PSCR
)
,

[L_LL_S] = LAYOUT_wrapper(
  ___________________BLANK___________________,                   __________________FUNCTION1________________,
  ___________________BLANK___________________,                   __________________FUNCTION2________________,
  ___________________BLANK___________________,                   __________________FUNCTION3________________,
  _______, _______, _______, _______, _______, KC_LCTL, KC_LALT, _______, _______, _______, _______, _______
)
,

[L_LL_E] = LAYOUT_wrapper(
  __________________L_LL_E_L1________________,                   __________________L_LL_E_R1________________,
  __________________L_LL_E_L2________________,                   __________________L_LL_E_R2________________,
  __________________L_LL_E_L3________________,                   __________________L_LL_E_R3________________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

// Uncomment any of these to add keyboard-specific code. Otherwise, they
// will use user defaults defined in the replicaJunction.h header file.

// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }

// void matrix_init_keymap(void) {};

// void matrix_scan_keymap(void) {};
