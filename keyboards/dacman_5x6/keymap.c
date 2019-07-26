#include QMK_KEYBOARD_H
#include "version.h"

extern keymap_config_t keymap_config;

enum dacman_5x6_replicaJunction_layers {
    L_BASE,
    L_LOWER,
    L_RAISE,
    L_ADJUST
};

enum dacman_5x6_replicaJunction_keycodes {
  RJ_MAKE = SAFE_RANGE,      // QMK make command
  RJ_QMKV,                   // QMK version
  RJ_EQ,                     // ==
  RJ_NEQ,                    // !=
  RJ_GEQ,                    // >=
  RJ_LEQ,                    // <=
  RJ_GEQR,                   // => ("greater than or equal - right")
  RJ_DUND,                   // $_
  RJ_SELS,                   // select * (used for PowerShell)
  RJ_4ECH,                   // | % {    (used for PowerShell)
  RJ_WHER,                   // | ? { $_ (used for PowerShell)
  DYNAMIC_MACRO_RANGE
};

// Per QMK documentation, this include must be below the keycode definitions
// https://docs.qmk.fm/#/feature_dynamic_macros
#include "dynamic_macro.h"

// Keycode aliases

#define ________ KC_TRNS
#define oooooooo KC_TRNS

#define SFT_TAB  LSFT(KC_TAB)
#define WIN_TAB  LGUI(KC_TAB)
#define WIN_L    LGUI(KC_L)

#define KC_BS_LT LT(L_LOWER, KC_BSPC)
#define KC_SP_LT LT(L_RAISE, KC_SPC)

#define KC_D_LT LT(L_MACRO, KC_D)
#define KC_H_LT LT(L_MOUSE, KC_H)

#define KC_DEL_C CTL_T(KC_DEL)
#define KC_ENT_A ALT_T(KC_ENT)

#define D_REC1  DYN_REC_START1
#define D_REC2  DYN_REC_START2
#define D_STOP  DYN_REC_STOP
#define D_PLAY1 DYN_MACRO_PLAY1
#define D_PLAY2 DYN_MACRO_PLAY2

#define TG_GAME TG(L_GAME)

// Application-specific shortcuts

#define M_CONSOL LCTL(KC_GRV)
#define M_SEARCH LCTL(LGUI(LALT(KC_S)))

#define M_ARS_LS LCTL(LGUI(LALT(KC_P)))
#define M_ARS_PT LCTL(LGUI(LALT(KC_V)))

//----------------------------------------------------------------------
// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_BASE] = LAYOUT_5x6(
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                          KC_6    ,KC_7    ,KC_8    ,KC_9   ,KC_0    ,KC_BSPC ,
     KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,                          KC_J    ,KC_L    ,KC_U    ,KC_Y   ,KC_SCLN ,KC_MINS ,
     KC_LSFT ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,                          KC_M    ,KC_N    ,KC_E    ,KC_I   ,KC_O    ,KC_QUOT ,
     KC_LCTL ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,                          KC_K    ,KC_H    ,KC_COMM ,KC_DOT ,KC_SLSH ,KC_BSLS ,
                       KC_LBRC ,KC_RBRC ,                                                              KC_PLUS, KC_EQL,
                                         KC_LSFT ,KC_BS_LT,                          KC_SP_LT,KC_RSFT ,
                                                  KC_TAB  ,KC_DEL_C,        KC_ENT_A,KC_DEL,
                                                  KC_LALT ,KC_GRV  ,        KC_LGUI ,KC_RCTL
  ),

  [L_LOWER] = LAYOUT_5x6(
     ________,________,________,________,________,________,                          ________,________,________,________,________,________,
     ________,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,________,                          ________,KC_P7   ,KC_P8   ,KC_P9   ,KC_ASTR ,________,
     ________,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,________,                          ________,KC_P4   ,KC_P5   ,KC_P6   ,KC_PIPE ,________,
     ________,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,________,                          KC_AMPR ,KC_P1   ,KC_P2   ,KC_P3   ,KC_BSLS ,________,
                       ________,________,                                                              KC_P0   ,KC_DOT  ,
                                         ________,oooooooo,                          oooooooo,KC_UNDS ,
                                                  ________,________,        ________,________,
                                                  ________,________,        ________,________
  ),

  [L_RAISE] = LAYOUT_5x6(
     ________,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                          KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,________,
     ________,________,________,________,M_CONSOL,M_ARS_LS,                          KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_DEL  ,________,
     ________,KC_LGUI ,KC_LSFT ,KC_LALT ,KC_LCTL ,________,                          KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_BSPC ,________,
     ________,________,________,________,M_SEARCH,M_ARS_PT,                          ________,SFT_TAB ,KC_TAB  ,WIN_TAB ,KC_PSCR ,________,
                       ________,________,                                                              ________,________,
                                         ________,oooooooo,                          oooooooo,________,
                                                  ________,________,        ________,________,
                                                  ________,________,        ________,________
  ),

  // Template
//   [L_TEMPLATE] = LAYOUT_5x6(
//      ________,________,________,________,________,________,                          ________,________,________,________,________,________,
//      ________,________,________,________,________,________,                          ________,________,________,________,________,________,
//      ________,________,________,________,________,________,                          ________,________,________,________,________,________,
//      ________,________,________,________,________,________,                          ________,________,________,________,________,________,
//                        ________,________,                                                              ________,________,
//                                          ________,________,                          ________,________,
//                                                   ________,________,        ________,________,
//                                                   ________,________,        ________,________
//   ),
};

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, L_LOWER, L_RAISE, L_ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
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
    }

    return true;
}