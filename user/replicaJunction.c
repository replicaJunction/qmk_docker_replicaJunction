#include QMK_KEYBOARD_H

#include "replicaJunction.h"
#include "vim.h"
#include "version.h"
#include "dynamic_macro.h"

extern uint8_t vim_cmd_layer(void) { return L_VIM; }

#ifdef TAP_DANCE_ENABLE
void dance_layer(qk_tap_dance_state_t *state, void *user_data) {
    uint8_t layer = biton32(layer_state);

    if (state->count >= 5)
    {
        // 5 or more taps resets the keyboard
        reset_keyboard();
    }
    #ifdef HAS_LAYER_QWERTY
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
    else
    {
        // Single tap sends Escape, and also turns off layers
        // That's mostly in case I get stuck and forget where I am
        layer_off(L_NUM);
        layer_off(L_EXTEND);
        layer_off(L_SYMBOL);
        #ifdef HAS_LAYER_QWERTY
            layer_off(L_QWERTY);
        #endif
        layer_off(L_VIM);

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

// // Runs just one time when the keyboard initializes.
// void matrix_init_user(void) {
//     // #ifdef REPLICAJUNCTION_UNICODE_ENABLE
//     // // Set Unicode input to use WinCompose
//     // // https://github.com/samhocevar/wincompose
//     // // set_unicode_input_mode(UC_WINC);
//     // set_unicode_input_mode(UC_WIN);

//     // #endif

//     matrix_init_keymap();
// };

#ifdef CONSOLE_ENABLE
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case L_VIM:
            uprintf("layer:vim (%u)\n", L_VIM);
            break;
        case L_MACRO:
            uprintf("layer:macro\n");
            break;
    }
    return state;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ( !process_record_dynamic_macro( keycode, record ) ) {
        return false;
    }

    if ( !process_record_vim( keycode, record) ) {
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

// ------------------------------------------------------------
// Keyboard layout definitions
// ------------------------------------------------------------

// This works because each keyboard defines the TEMPLATE() macro
// in its own config.h file, so each board decides where the keys
// are physically placed by itself.

// I use an Ergodox as my "master" for two reasons:
// 1. It was the first keyboard I built
// 2. It's the largest keyboard I own (76 keys)

// Since I don't use any QMK-powered "traditional" keyboards, it
// works very well for me.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[L_BASE] = TEMPLATE(
  KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_GRV  ,         TG_GAME ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_EQL ,
  KX_ECTL ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,KC_LBRC ,         KC_DEL  ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS,
  KC_TAB  ,KC_A    ,KC_R_LT ,KC_S_LT ,KC_T    ,KC_G    ,                           KC_M    ,KC_N    ,KC_E_LT ,KC_I    ,KC_O    ,KC_QUOT,
  KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_D_LT ,KC_V    ,KC_RBRC ,         KC_LOCK ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT,
  TD_LAYR ,TD_LAYR ,V_START ,KC_TAB  ,KC_LSFT ,                                             KC_RSFT ,KC_MINS ,KC_QUOT ,KC_EQL  ,TT_NUM ,

                                               KC_LCTL ,KC_LALT ,         KC_RCTL ,KC_RALT ,
                                                        KC_LGUI ,         KC_RGUI ,
                                      KC_BSPC ,KX_DCTL ,KC_PGDN ,         KC_DOWN ,KX_NALT ,KX_SPAC
),


#ifdef HAS_LAYER_QWERTY
[L_QWERTY] = TEMPLATE(
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  _______ ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,_______ ,         _______ ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,_______ ,
  _______ ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                           KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,_______ ,
  _______ ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,_______ ,         _______ ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______ ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______
),
#endif


[L_NUM] = TEMPLATE(
  _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,         _______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  _______ ,_______ ,_______ ,_______ ,KC_LBRC ,KC_RBRC ,_______ ,         _______ ,KC_COLN ,KC_NUM7 ,KC_NUM8 ,KC_NUM9 ,KC_NUMS ,KC_F12  ,
  _______ ,_______ ,_______ ,ooooooo ,KC_COMM ,_______ ,                           KC_HASH ,KC_NUM4 ,KC_NUM5 ,KC_NUM6 ,KC_NUMA ,KC_BSPC ,
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,KC_COMM ,KC_NUM1 ,KC_NUM2 ,KC_NUM3 ,KC_NUMM ,KC_TAB  ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                             KC_NUM0 ,KC_NUMD ,KC_NUMQ ,KC_NUMP ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      ooooooo ,_______ ,_______ ,         _______ ,KC_NUME ,_______
),



[L_SYMBOL] = TEMPLATE(
  _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,         _______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_TILD ,_______ ,         _______ ,_______ ,KC_AMPR ,_______ ,_______ ,_______ ,KC_F12  ,
  _______ ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV  ,                           _______ ,KC_PIPE ,ooooooo ,_______ ,_______ ,KC_BSPC ,
  _______ ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,_______ ,_______ ,         _______ ,_______ ,KC_BSLS ,_______ ,_______ ,_______ ,KC_TAB  ,
  _______ ,_______ ,_______, _______, _______ ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______

),



[L_EXTEND] = TEMPLATE(
  _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F11  ,         KC_F12  ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
  _______ ,_______ ,ALT_F4  ,KC_APP  ,KX_CGR  ,KX_PAST ,KC_VOLU ,         _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_DEL  ,_______ ,
  _______ ,KC_LGUI ,KC_LSFT ,KC_LALT ,KC_LCTL ,_______ ,                           KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_BSPC ,KC_MENU ,
  _______ ,_______ ,_______ ,_______ ,KX_SRCH ,KX_ARSC ,KC_VOLD ,         _______ ,_______ ,KX_STAB ,KC_TAB  ,KX_WTAB ,KC_INS  ,KC_PSCR ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                             _______ ,_______ ,_______ ,KC_PSCR ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______, _______ ,_______ ,         _______ ,_______ ,_______

),



[L_FUNCTION] = TEMPLATE(
  _______ ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,_______ ,         _______ ,KC_F16  ,KC_F17  ,KC_F18  ,KC_F19  ,KC_F20  ,_______ ,
  _______ ,_______ ,_______ ,M_LCLIK ,M_RCLIK ,M_MCLIK, _______ ,         _______ ,KC_VOLU ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
  _______ ,KC_LGUI ,KC_LSFT ,KC_LALT ,KC_LCTL ,M_WHLUP,                            KC_MUTE ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,_______ ,
  _______ ,M_LEFT  ,M_DOWN,  M_UP    ,M_RIGHT ,M_WHLDN, _______ ,         _______ ,KC_VOLD ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,_______ ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______

),



[L_MACRO] = TEMPLATE(
  _______ ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,_______ ,         _______ ,KC_F16  ,KC_F17  ,KC_F18  ,KC_F19  ,KC_F20  ,_______ ,
  _______ ,RJ_QMKV ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,RJ_DUND ,RJ_SELS ,RJ_4ECH ,RJ_WHER ,_______ ,
  _______ ,RJ_MAKE ,_______ ,_______ ,_______ ,_______ ,                           RJ_NEQ  ,RJ_EQ   ,RJ_GEQR ,RJ_GEQ  ,RJ_LEQ  ,_______ ,
  _______ ,WIN_L   ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  _______ ,_______ ,_______ ,_______ ,_______ ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______
),


#ifdef HAS_LAYER_GAMING
[L_GAMING] = TEMPLATE(
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  KC_ESC  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  _______ ,_______ ,KC_R    ,KC_S    ,_______ ,_______ ,                           _______ ,_______ ,KC_E    ,_______ ,_______ ,_______ ,
  KC_LSFT ,_______ ,_______ ,_______ ,KC_D    ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______ ,KC_UP,   KC_SLSH,
  _______ ,_______ ,_______ ,KC_LALT ,KC_LCTL ,                                             _______ ,_______ ,KC_LEFT, KC_DOWN, KC_RGHT,

                                               _______ ,_______ ,         M_MCLIK ,_______ ,
                                                        _______ ,         M_RCLIK ,
                                      KC_SPC,  KC_LSFT, _______ ,         M_LCLIK ,KC_ENT  ,KC_BSPC

),
#endif

[L_VIM] = TEMPLATE(
  _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______, _______, _______, _______, _______ ,_______ ,
  _______ ,_______ ,VIM_W   ,_______ ,VIM_P   ,VIM_B   ,_______ ,         _______ ,VIM_J   ,VIM_L   ,VIM_U   ,VIM_Y   ,_______ ,_______ ,
  _______ ,VIM_A   ,_______ ,VIM_S   ,_______ ,VIM_G   ,                           _______ ,_______ ,VIM_E   ,VIM_I   ,VIM_O   ,_______ ,
  _______ ,_______ ,_______ ,VIM_C   ,VIM_D   ,VIM_V   ,_______ ,         _______ ,VIM_K   ,VIM_H   ,V_DOT   ,V_COMMA ,_______ ,_______ ,
  _______ ,_______ ,VIM_ESC ,_______ ,V_SHIFT ,                                             V_SHIFT ,_______ ,_______ ,_______ ,_______ ,

                                               _______ ,_______ ,         _______ ,_______ ,
                                                        _______ ,         _______ ,
                                      _______ ,_______ ,_______ ,         _______ ,_______ ,_______
)

};