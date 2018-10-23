#include "replicaJunction.h"
#include "version.h"

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

// Tap Dance Definitions
// Note - this needs to come AFTER the function is declared
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_LAYER_TOGGLE] = ACTION_TAP_DANCE_FN(dance_layer)
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
    #ifdef REPLICAJUNCTION_UNICODE_ENABLE
    // Set Unicode input to use WinCompose
    // https://github.com/samhocevar/wincompose
    // set_unicode_input_mode(UC_WINC);
    set_unicode_input_mode(UC_WIN);

    #endif

    matrix_init_keymap();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    matrix_scan_keymap();
}

#ifdef REPLICAJUNCTION_UNICODE_ENABLE
inline void tap(uint16_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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


        #ifdef REPLICAJUNCTION_UNICODE_ENABLE
        case U_QUERY:
          if (record->event.pressed) {
            switch (get_unicode_input_mode()) {
              case UC_LNX:
                SEND_STRING ("Unicode: Linux");
                break;
              case UC_OSX:
                SEND_STRING ("Unicode: Mac");
                break;
              case UC_WIN:
                SEND_STRING ("Unicode: Win");
                break;
              case UC_WINC:
                SEND_STRING ("Unicode: WinCompose");
                break;
            }
          }
          return false;
          break;
        case U_TABLE:
            if (record->event.pressed) {
                send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
            }
            return false;
            break;
        // case U_TABLE:
        //   if (record->event.pressed) {
        //     register_code(KC_RSFT);
        //     tap(KC_9);
        //     unregister_code(KC_RSFT);
        //     process_unicode((0x256F|QK_UNICODE), record);   // Arm
        //     process_unicode((0x00B0|QK_UNICODE), record);   // Eye
        //     process_unicode((0x25A1|QK_UNICODE), record);   // Mouth
        //     process_unicode((0x00B0|QK_UNICODE), record);   // Eye
        //     register_code(KC_RSFT);
        //     tap(KC_0);
        //     unregister_code(KC_RSFT);
        //     process_unicode((0x256F|QK_UNICODE), record);   // Arm
        //     tap(KC_SPC);
        //     process_unicode((0x0361|QK_UNICODE), record);   // Flippy
        //     tap(KC_SPC);
        //     process_unicode((0x253B|QK_UNICODE), record);   // Table
        //     process_unicode((0x2501|QK_UNICODE), record);   // Table
        //     process_unicode((0x253B|QK_UNICODE), record);   // Table
        //   }
        //   return false;
        //   break;
        // case U_TABL2: // ┬──┬ ノ( ゜-゜ノ)
        //   if (record->event.pressed) {
        //     process_unicode((0x252C|QK_UNICODE), record);   // Table
        //     process_unicode((0x2500|QK_UNICODE), record);   // Table
        //     process_unicode((0x2500|QK_UNICODE), record);   // Table
        //     process_unicode((0x252C|QK_UNICODE), record);   // Table
        //     tap(KC_SPC);
        //     process_unicode((0x30CE|QK_UNICODE), record);   // Arm
        //     register_code(KC_RSFT);
        //     tap(KC_9);
        //     unregister_code(KC_RSFT);
        //     tap(KC_SPC);
        //     process_unicode((0x309C|QK_UNICODE), record);   // Eye
        //     tap(KC_MINS);
        //     process_unicode((0x309C|QK_UNICODE), record);   // Eye
        //     process_unicode((0x30CE|QK_UNICODE), record);   // Arm
        //     register_code(KC_RSFT);
        //     tap(KC_0);
        //     unregister_code(KC_RSFT);
        //   }
        //   return false;
        //   break;
        case U_SHRUG: // ¯\_(ツ)_/¯
          if (record->event.pressed) {
            process_unicode((0x00AF|QK_UNICODE), record);   // Hand
            tap(KC_BSLS);                                   // Arm
            register_code(KC_RSFT);
            tap(KC_UNDS);                                   // Arm
            tap(KC_LPRN);                                   // Head
            unregister_code(KC_RSFT);
            process_unicode((0x30C4|QK_UNICODE), record);   // Face
            register_code(KC_RSFT);
            tap(KC_RPRN);                                   // Head
            tap(KC_UNDS);                                   // Arm
            unregister_code(KC_RSFT);
            tap(KC_SLSH);                                   // Arm
            process_unicode((0x00AF|QK_UNICODE), record);   // Hand
          }
          return false;
          break;
        case U_DLOOK:       // ಠ_ಠ
          if(record->event.pressed){
            process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
            register_code(KC_RSFT);
            tap(KC_MINS);
            unregister_code(KC_RSFT);
            process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
          }
          return false;
          break;
        #endif
    }

    return process_record_keymap(keycode, record);
};
