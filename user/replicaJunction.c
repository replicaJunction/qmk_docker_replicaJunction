#include "replicaJunction.h"
#include "version.h"
#include "dynamic_macro.h"
#include "process_leader.h"

LEADER_EXTERNS();

#ifdef TAP_DANCE_ENABLE
void dance_layer(qk_tap_dance_state_t *state, void *user_data)
{
    uint8_t layer = biton32(layer_state);

    if (state->count >= 5)
    {
        // 5 or more taps resets the keyboard
        reset_keyboard();
    }
    #ifdef L_QWERTY
    else if (state->count == 3)
    {
        // Triple tap changes to QWERTY layer
        if (layer == L_QWERTY)
        {
            layer_off(L_QWERTY);
        }
        else
        {
            layer_on(L_QWERTY);
        }
    }
    #endif
    #ifdef L_NUM
    else if (state->count == 2)
    {
        // Double tap toggles Number layer
        if (layer == L_NUM)
        {
            layer_off(L_NUM);
        }
        else
        {
            layer_on(L_NUM);
        }
    }
    #endif
    else
    {
        // Single tap sends Escape, and also turns off layers
        // That's mostly in case I get stuck and forget where I am
        #ifdef L_NUM
            layer_off(L_NUM);
        #endif
        #ifdef L_EXTEND
            layer_off(L_EXTEND);
        #endif
        #ifdef L_SYMBOL
            layer_off(L_SYMBOL);
        #endif
        #ifdef L_QWERTY
            layer_off(L_QWERTY);
        #endif

        register_code(KC_ESC);
        unregister_code(KC_ESC);
    }
};

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

// Tap Dance Definitions
// Note - this needs to come AFTER the function is declared
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_LAYER_TOGGLE] = ACTION_TAP_DANCE_FN(dance_layer),
        [TD_MACRO]        = ACTION_TAP_DANCE_FN(dance_macro)
};

#endif // TAP_DANCE_ENABLE

// These functions can be overridden in individual keymap files.
// This allows a user function to be shared for all my keyboards, while each
// keyboard can also have a keyboard-specific section.

// Note that keymaps don't need to override these if there's nothing to
// override them with.
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
        return true;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // #ifdef REPLICAJUNCTION_UNICODE_ENABLE
    // // Set Unicode input to use WinCompose
    // // https://github.com/samhocevar/wincompose
    // // set_unicode_input_mode(UC_WINC);
    // set_unicode_input_mode(UC_WIN);

    // #endif

    matrix_init_keymap();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    matrix_scan_keymap();

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_T) {
            register_code(KC_TAB);
            unregister_code(KC_TAB);
        }

        SEQ_ONE_KEY(KC_O) {
            register_code(KC_LGUI);
            unregister_code(KC_LGUI);
        }

        SEQ_ONE_KEY(KC_Q) {
            register_code(KC_LALT);
            register_code(KC_F4);

            unregister_code(KC_F4);
            unregister_code(KC_LALT);
        }

        // Git

        SEQ_TWO_KEYS(KC_G, KC_A) {
            SEND_STRING("git add .");
        }
        SEQ_TWO_KEYS(KC_G, KC_D) {
            SEND_STRING("git diff");
        }
        SEQ_THREE_KEYS(KC_G, KC_D, KC_S) {
            SEND_STRING("git diff --staged");
        }
        SEQ_TWO_KEYS(KC_G, KC_L) {
            SEND_STRING("git log");
        }
        SEQ_THREE_KEYS(KC_G, KC_L, KC_O) {
            SEND_STRING("git log --oneline");
        }
        SEQ_TWO_KEYS(KC_G, KC_F) {
            SEND_STRING("git fetch");
        }
        SEQ_TWO_KEYS(KC_G, KC_O) {
            SEND_STRING("git checkout");
        }
        SEQ_TWO_KEYS(KC_G, KC_P) {
            SEND_STRING("git pull");
        }
        SEQ_TWO_KEYS(KC_G, KC_S) {
            SEND_STRING("git status");
        }
        SEQ_TWO_KEYS(KC_G, KC_C) {
            SEND_STRING("git commit -m ''"SS_TAP(X_LEFT));
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) {
            SEND_STRING("git commit --amend");
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ( !process_record_dynamic_macro( keycode, record ) ) {
        return false;
    }

    switch(keycode)
    {
        case RJ_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (record->event.pressed)
                return true;

            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
            #if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                                    ":dfu"
            #elif defined(BOOTLOADER_HALFKAY)
                                    ":teensy"
            #elif defined(BOOTLOADER_CATERINA)
                                    ":avrdude"
            #endif // bootloader options
                                    //SS_TAP(X_ENTER)
                                    );
            return false;
        case RJ_QMKV:
            if (record->event.pressed)
                return true;

            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case RJ_EQ:
            if (record->event.pressed)
                return true;

            SEND_STRING("==");
            return false;
        case RJ_NEQ:
            if (record->event.pressed)
                return true;

            SEND_STRING("!=");
            return false;
        case RJ_GEQ:
            if (record->event.pressed)
                return true;

            SEND_STRING(">=");
            return false;
        case RJ_LEQ:
            if (record->event.pressed)
                return true;

            SEND_STRING("<=");
            return false;
        case RJ_GEQR:
            if (record->event.pressed)
                return true;

            SEND_STRING("=>");
            return false;
        case RJ_DUND:
            if (record->event.pressed)
                return true;

            SEND_STRING("$_");
            return false;
        case RJ_SELS:
            if (record->event.pressed)
                return true;

            SEND_STRING("select *");
            return false;

        case RJ_4ECH:
            if (record->event.pressed)
                return true;

            SEND_STRING(" | % { ");
            return false;

        case RJ_WHER:
            if (record->event.pressed)
                return true;

            SEND_STRING(" | ? { $_");
            return false;

        // case U_QUERY:
        //   if (record->event.pressed) {
        //     switch (get_unicode_input_mode()) {
        //       case UC_LNX:
        //         SEND_STRING ("Unicode: Linux");
        //         break;
        //       case UC_OSX:
        //         SEND_STRING ("Unicode: Mac");
        //         break;
        //       case UC_WIN:
        //         SEND_STRING ("Unicode: Win");
        //         break;
        //       case UC_WINC:
        //         SEND_STRING ("Unicode: WinCompose");
        //         break;
        //     }
        //   }
        //   return false;
        //   break;
    }

    return process_record_keymap(keycode, record);
};
