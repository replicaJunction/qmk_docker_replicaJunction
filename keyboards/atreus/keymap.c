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
  _________________L_COLEMAK_L1______________,                   _________________L_COLEMAK_R1______________,
  _________________L_COLEMAK_L2______________,                   _________________L_COLEMAK_R2______________,
  _________________L_COLEMAK_L3______________,                   _________________L_COLEMAK_R3______________,
  TD_LAYR, KC_LGUI, KC_TAB,  KC_LSFT, KX_BKNM, KX_DCTL, KX_NALT, KX_SPAC, KC_RSFT, KC_MINS, KC_QUOT, KC_EQL
)
,

[L_NUM] = LAYOUT(
  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_SLSH,                   KC_COLN, KC_7,    KC_8,    KC_9,    KC_SLSH,
  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_PIPE,                   KC_HASH, KC_4,    KC_5,    KC_6,    KC_ASTR,
  KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLS,                   KC_BSPC, KC_1,    KC_2,    KC_3,    KC_MINS,
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


[L_LL_R] = LAYOUT_wrapper(
  __________________L_LL_R_L1________________,                   __________________L_LL_R_R1________________,
  __________________L_LL_R_L2________________,                   __________________L_LL_R_R2________________,
  __________________L_LL_R_L3________________,                   __________________L_LL_R_R3________________,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  KC_EQL,  KC_PLUS
)
,

[L_LL_S] = LAYOUT_wrapper(
  __________________L_LL_S_L1________________,                   __________________L_LL_S_R1________________,
  __________________L_LL_S_L2________________,                   __________________L_LL_S_R2________________,
  __________________L_LL_S_L3________________,                   __________________L_LL_S_R3________________,
  _______, _______, _______, _______, _______, KC_LCTL, KC_LALT, _______, _______, _______, _______, _______
)
,

[L_LL_E] = LAYOUT_wrapper(
  __________________L_LL_E_L1________________,                   __________________L_LL_E_R1________________,
  __________________L_LL_E_L2________________,                   __________________L_LL_E_R2________________,
  __________________L_LL_E_L3________________,                   __________________L_LL_E_R3________________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
,

[L_LL_I] = LAYOUT_wrapper(
  __________________L_LL_I_L1________________,                   __________________L_LL_I_R1________________,
  __________________L_LL_I_L2________________,                   __________________L_LL_I_R2________________,
  __________________L_LL_I_L3________________,                   __________________L_LL_I_R3________________,
  _______, KC_AMPR, KC_LABK, KC_RABK, _______, _______, _______, _______, _______, _______, _______, _______
)

};

// Uncomment any of these to add keyboard-specific code. Otherwise, they
// will use user defaults defined in the replicaJunction.h header file.

// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }

// void matrix_init_keymap(void) {};

// void matrix_scan_keymap(void) {};
