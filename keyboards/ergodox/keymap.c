/*
 * Keyboard: Ergodox
 * Keymap:   replicaJunction
 * Version:  2.3
 */

#include QMK_KEYBOARD_H
#include "config.h"
#include "replicaJunction.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// If using the L_COLEMAK, L_QWERTY, etc. shortcuts, these should
// use the LAYOUT_ergodox_wrapper macro.
// Otherwise, they should use LAYOUT_ergodox

[L_COLEMAK] = LAYOUT_ergodox_pretty_wrapper(
  KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_GRV  ,         TG_GAME ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_EQL ,
  KX_ECTL ,__________________COLEMAK_L1_______________ ,KC_LBRC ,         KC_DEL  ,__________________COLEMAK_R1_______________ ,KC_BSLS,
  KC_TAB  ,__________________COLEMAK_L2_______________ ,                           __________________COLEMAK_R2_______________ ,KC_QUOT,
  KC_LSFT ,__________________COLEMAK_L3_______________ ,KC_RBRC ,         KC_LOCK ,__________________COLEMAK_R3_______________ ,KC_RSFT,
  TD_LAYR ,TD_LAYR ,KC_LGUI ,KC_LALT ,KC_LCTL ,                                    KC_RALT ,KC_MINS ,KC_QUOT ,KC_EQL  ,TT_NUM ,

                                               KC_LCTL ,KC_LALT ,         KC_LEFT ,KC_RGHT ,
                                                        KC_LGUI ,         KC_UP   ,
                                      KX_BKNM ,KX_DCTL ,KC_PGDN ,         KC_DOWN ,KX_NALT ,KX_SPAC
),



[L_QWERTY] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_EQL  ,
  _______ ,_________________L_QWERTY_L1_______________ ,_______ ,         _______ ,_________________L_QWERTY_R1_______________ ,_______ ,
  _______ ,_________________L_QWERTY_L2_______________ ,                           _________________L_QWERTY_R2_______________ ,KC_QUOT ,
  _______ ,_________________L_QWERTY_L3_______________ ,_______ ,         KC_LOCK ,_________________L_QWERTY_R3_______________ ,KC_RSPC ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                           KC_RALT ,KC_MINS ,KC_QUOT ,KC_EQL  ,TT_NUM  ,

                                               _______ ,_______ ,         KC_LEFT ,KC_RGHT ,
                                                        _______ ,         KC_UP   ,
                                      _______ ,_______ ,_______ ,         KC_DOWN ,KX_NALT ,KX_SPAC
),



[L_NUM] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,         _______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  _______ ,_______ ,_______ ,_______ ,KC_LBRC ,KC_RBRC ,_______ ,         _______ ,__________________L_NUMBER_R1______________ ,KC_F12  ,
  _______ ,_______ ,_______ ,ooooooo ,KC_COMM ,_______ ,                           __________________L_NUMBER_R2______________ ,KC_BSPC ,
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,__________________L_NUMBER_R3______________ ,KC_TAB  ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                    KC_P0   ,KC_PDOT ,KC_PEQL ,KC_PPLS ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      ooooooo ,_______ ,_______ ,         _______ ,KC_PENT ,_______
),



[L_SYMBOL] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,         _______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  _______ ,__________________L_SYMBOL_L1______________ ,_______ ,         _______ ,__________________L_SYMBOL_R1______________ ,KC_F12  ,
  _______ ,__________________L_SYMBOL_L2______________ ,                           __________________L_SYMBOL_R2______________ ,KC_BSPC ,
  _______ ,__________________L_SYMBOL_L3______________ ,_______ ,         _______ ,__________________L_SYMBOL_R3______________ ,KC_TAB  ,
  _______ ,_______ ,_______, _______, _______ ,                                    KC_P0   ,KC_PDOT ,KC_PEQL ,KC_PPLS ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,KC_PENT ,_______

),



[L_EXTEND] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,           KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ ,
  _______ ,_________________L_EXTEND_L1_______________, KC_VOLU ,         _______ ,_________________L_EXTEND_R1_______________, _______ ,
  _______ ,_________________L_EXTEND_L2_______________,                            _________________L_EXTEND_R2_______________, KC_MENU,
  _______ ,_________________L_EXTEND_L3_______________, KC_VOLD,          _______ ,_________________L_EXTEND_R3_______________, KC_PSCR,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                    _______ ,_______ ,_______ ,KC_PSCR, _______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______, _______ ,_______ ,         _______ ,_______ ,_______

),



[L_FUNCTION] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,_______ ,         _______ ,KC_F16  ,KC_F17  ,KC_F18  ,KC_F19  ,KC_F20  ,_______ ,
  _______ ,_______ ,_______ ,M_LCLIK ,M_RCLIK ,M_MCLIK, _______ ,         _______ ,__________________FUNCTION1________________ ,_______ ,
  _______ ,KC_LGUI ,KC_LSFT ,KC_LALT ,KC_LCTL ,M_WHLUP,                            __________________FUNCTION2________________ ,_______ ,
  _______ ,M_LEFT  ,M_DOWN,  M_UP    ,M_RIGHT ,M_WHLDN, _______ ,         _______ ,__________________FUNCTION3________________ ,_______ ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                    _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______

),



[L_MACRO] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,_______ ,         _______ ,KC_F16  ,KC_F17  ,KC_F18  ,KC_F19  ,KC_F20  ,_______ ,
  _______ ,__________________MACRO_L1_________________ ,_______ ,         _______ ,__________________MACRO_R1_________________ ,_______ ,
  _______ ,__________________MACRO_L2_________________ ,                           __________________MACRO_R2_________________ ,_______ ,
  _______ ,__________________MACRO_L3_________________ ,_______ ,         _______ ,__________________MACRO_R3_________________ ,_______ ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                    _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______
),



[L_GAMING] = LAYOUT_ergodox_pretty_wrapper(
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  KC_ESC  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  _______ ,_______ ,KC_R    ,KC_S    ,_______ ,_______ ,                           _______ ,_______ ,KC_E    ,KC_I    ,_______ ,_______ ,
  KC_LSFT, _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,KC_UP,   KC_SLSH,
  _______ ,_______ ,_______ ,KC_LALT ,KC_LCTL ,                                    _______ ,_______ ,KC_LEFT, KC_DOWN, KC_RGHT,

                                               _______ ,_______ ,         M_MCLIK ,_______ ,
                                                        _______ ,         M_RCLIK ,
                                      KC_SPC,  KC_LSFT, _______ ,         M_LCLIK ,KC_ENT  ,KC_BSPC

)

};

// The normal QMK functions ending in _user are overridden in the
// replicaJunction userspace. Those functions handle my global
// settings, and redirect to these _keymap functions if something
// is unhandled. This allows me to keep most of my global preferences
// in one place while still allowing keyboard-specific code.

// The idea was shamelessly copied from the amazing Drashna.

// Nothing to do here, so I've commented it out.
// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//   return true;
// }

// void matrix_init_keymap(void) {};

void matrix_scan_keymap(void) {

    uint8_t layer = biton32(layer_state);
    // uint8_t default_layer = biton32(layer_state);

    ergodox_board_led_off();

    switch (layer) {
        case L_COLEMAK:
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            break;
        case L_NUM:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_off();
            break;
        case L_EXTEND:
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_on();
            break;
        case L_FUNCTION:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case L_GAMING:
            ergodox_right_led_1_off();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
