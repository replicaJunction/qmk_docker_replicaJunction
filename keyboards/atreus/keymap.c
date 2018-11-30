/*
 * Keyboard: Atreus
 * Keymap:   replicaJunction
 * Version:  2.3
 */

#include QMK_KEYBOARD_H
#include "replicaJunction.h"

// Required for Vim emulation - define which layer has the Vim keyboard commands
extern uint8_t vim_cmd_layer(void) { return L_VIM; }

// These keymaps use "key groups" defined in replicaJunction.h.

// If using a key group, use LAYOUT_wrapper();
// otherwise, use LAYOUT()

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[L_COLEMAK] = LAYOUT_wrapper(
  __________________COLEMAK_L1_EX____________,                   __________________COLEMAK_R1_EX____________,
  __________________COLEMAK_L2_EX____________,                   __________________COLEMAK_R2_EX____________,
  __________________COLEMAK_L3_EX____________,                   __________________COLEMAK_R3_EX____________,
  TD_LAYR, VIM_START,KC_TAB,  KC_LSFT, KC_BSPC, KX_DCTL, KX_NALT, KX_SPAC, KC_RSFT, KC_MINS, KC_QUOT, KC_EQL
)
,

[L_NUM] = LAYOUT_wrapper(
  __________________L_NUMBER_L1______________,                   __________________L_NUMBER_R1______________,
  __________________L_NUMBER_L2______________,                   __________________L_NUMBER_R2______________,
  __________________L_NUMBER_L3______________,                   __________________L_NUMBER_R3______________,
  _______, _______, _______, _______, _______, _______, KC_ENT,  _______, KC_0,    KC_DOT,  KC_EQL,  KC_PLUS
)
,

[L_SYMBOL] = LAYOUT_wrapper(
  __________________L_SYMBOL_L1______________,                   __________________L_SYMBOL_R1______________,
  __________________L_SYMBOL_L2______________,                   __________________L_SYMBOL_R2______________,
  __________________L_SYMBOL_L3______________,                   __________________L_SYMBOL_R3______________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
,

[L_EXTEND] = LAYOUT_wrapper(
  _________________L_EXTEND_L1_______________,                   _________________L_EXTEND_R1_______________,
  _________________L_EXTEND_L2_______________,                   _________________L_EXTEND_R2_______________,
  _________________L_EXTEND_L3_______________,                   _________________L_EXTEND_R3_______________,
  _______, _______, _______, _______, _______,  KC_DEL, KC_ENT,  ooooooo, _______, _______, _______, KC_PSCR
)
,

[L_FUNCTION] = LAYOUT_wrapper(
  ___________________BLANK___________________,                   __________________FUNCTION1________________,
  ___________________BLANK___________________,                   __________________FUNCTION2________________,
  ___________________BLANK___________________,                   __________________FUNCTION3________________,
  _______, _______, _______, _______, _______, KC_LCTL, KC_LALT, _______, _______, _______, _______, _______
)
,

[L_MACRO] = LAYOUT_wrapper(
  __________________MACRO_L1_________________,                   __________________MACRO_R1_________________,
  __________________MACRO_L2_________________,                   __________________MACRO_R2_________________,
  __________________MACRO_L3_________________,                   __________________MACRO_R3_________________,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
,

[L_VIM] = LAYOUT_wrapper(
  __________________COLEMAK_L1_VIM___________,                   __________________COLEMAK_R1_VIM___________,
  __________________COLEMAK_L2_VIM___________,                   __________________COLEMAK_R2_VIM___________,
  __________________COLEMAK_L3_VIM___________,                   __________________COLEMAK_R3_VIM___________,
  _______, VIM_ESC, _______, VIM_SFT, _______, _______, _______, _______, VIM_SFT, VIM_DOT, VIM_COM, _______
)

};

// Uncomment any of these to add keyboard-specific code. Otherwise, they
// will use user defaults defined in the replicaJunction.h header file.

// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }

// void matrix_init_keymap(void) {};

// void matrix_scan_keymap(void) {};
