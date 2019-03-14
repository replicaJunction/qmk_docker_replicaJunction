#include QMK_KEYBOARD_H
#include "replicaJunction.h"

uint32_t layer_state_set_kb(uint32_t state) {
    switch (biton32(state)) {
        case L_BASE:
            ergodox_board_led_off();
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            break;
        case L_QWERTY:
            ergodox_board_led_on();
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            break;
        case L_NUM:
            ergodox_board_led_off();
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_off();
            break;
        case L_EXTEND:
            ergodox_board_led_off();
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_on();
            break;
        case L_GAMING:
            ergodox_board_led_on();
            ergodox_right_led_1_off();
            ergodox_right_led_2_on();
            ergodox_right_led_3_off();
            break;
        case L_VIM:
            ergodox_board_led_on();
            ergodox_right_led_1_on();
            ergodox_right_led_2_off();
            ergodox_right_led_3_off();
            break;
        default:
            // none
            break;
    }

    return state;
};
