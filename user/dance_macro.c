#include QMK_KEYBOARD_H
#include "dynamic_macro.h"

#include "dance_macro.h"

void dance_macro( qk_tap_dance_state_t *state, void *user_data) {
    if ( state->count > 3 )
        return;

    keyrecord_t kr;
    kr.event.pressed = false;
    uint16_t action = DYN_REC_STOP;

    if ( state->count == 1 ) {
        action = DYN_MACRO_PLAY1;
    }
    else if ( state->count == 2 ) {
        action = DYN_REC_STOP;
        kr.event.pressed = true;
    }
    else if ( state->count == 3 ) {
        action = DYN_REC_START1;
    }

    process_record_dynamic_macro( action, &kr );
}