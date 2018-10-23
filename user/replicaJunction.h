#pragma once

#include "quantum.h"

#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
#define REPLICAJUNCTION_UNICODE_ENABLE
#include "replicaJunction_unicode.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Keymap definitions
///////////////////////////////////////////////////////////////////////////////

// Keyboard aliases
#define _______ KC_TRNS
#define ooooooo KC_TRNS

#define MO_FUNC MO(L_FUNC)
#define TT_NUM  TT(L_NUM)
#define TG_GAME TG(L_GAMING)
#define OSL_SYM OSL(L_SYMBOL)

#define OSM_LSF OSM(MOD_LSFT)
#define OSM_RSF OSM(MOD_RSFT)

#define KX_CTSF LCTL(KC_LSFT)
#define KX_STAB LSFT(KC_TAB)
#define KX_WTAB LGUI(KC_TAB)
#define KX_CGR  LCTL(KC_GRV)
#define KX_PAST LCTL(LGUI(LALT(KC_V)))
#define KX_ARSC LCTL(LGUI(LALT(KC_P)))
#define KX_SRCH LCTL(LGUI(LALT(KC_S)))

#define KX_BKNM LT(L_NUM, KC_BSPC)
#define KX_DCTL CTL_T(KC_DEL)
#define KX_NALT ALT_T(KC_ENT)
#define KX_ECTL CTL_T(KC_ESC)
#define KX_SPAC LT(L_EXTEND, KC_SPC)

#define KX_Z_MT CTL_T(KC_Z)
#define KX_X_MT GUI_T(KC_X)
#define KX_C_MT MT(MOD_LCTL | MOD_LALT, KC_C)
#define KX_D_MT ALT_T(KC_D)

#define KX_SLMT CTL_T(KC_SLSH)
#define KX_DOMT GUI_T(KC_DOT)
#define KX_COMT MT(MOD_LCTL | MOD_LALT, KC_COMM)
#define KX_H_MT ALT_T(KC_H)

#ifdef L_LL_R
    #define KC_R_LT LT(L_LL_R, KC_R)
#else
    #define KC_R_LT KC_R
#endif

#ifdef L_LL_S
    #define KC_S_LT LT(L_LL_S, KC_S)
#else
    #define KC_S_LT KC_S
#endif

#ifdef L_LL_E
    #define KC_E_LT LT(L_LL_E, KC_E)
#else
    #define KC_E_LT KC_E
#endif

#ifdef L_LL_I
    #define KC_I_LT LT(L_LL_I, KC_I)
#else
    #define KC_I_LT KC_I
#endif

#ifdef L_LL_D
    #define KC_D_LT LT(L_LL_D, KC_D)
#else
    #define KC_D_LT KC_D
#endif

// "Macro" functions
enum userspace_custom_keycodes {
    RJ_MAKE = SAFE_RANGE,  // QMK make command
    RJ_QMKV,               // QMK version
    RJ_EQ,                 // ==
    RJ_NEQ,                // !=
    RJ_GEQ,                // >=
    RJ_LEQ,                // <=
    RJ_GEQR,               // => ("greater than or equal - right")
    RJ_DUND,               // $_
    RJ_SELS,               // select * (used for PowerShell)

    #ifdef REPLICAJUNCTION_UNICODE_ENABLE
    U_QUERY,               // Display Unicode input mode
    U_TABLE,               // Table flip
    // U_TABL2,               // Reset the table
    U_SHRUG,               // Shrug
    U_DLOOK,               // Look of disapproval
    #endif

    RJ_MUTE,               // Discord mute (GUI+Shift+M)
    RJ_DEAF,               // Discord deafen (GUI+Shift+D)
    RJ_DOVR                // Toggle Discord overlay (GUI+Shift+O)
};

// Mouse keys
#define M_UP KC_MS_UP
#define M_DOWN KC_MS_DOWN
#define M_LEFT KC_MS_LEFT
#define M_RIGHT KC_MS_RIGHT
#define M_LCLIK KC_MS_BTN1
#define M_RCLIK KC_MS_BTN2
#define M_MCLIK KC_MS_BTN3
#define M_WHLUP KC_WH_U
#define M_WHLDN KC_WH_D

// // Used in macro definitions
// #define TAP(code) register_code (code); unregister_code (code);

// Tap Dance
#ifdef TAP_DANCE_ENABLE
#define TD_LAYER_TOGGLE 0
extern void dance_layer(qk_tap_dance_state_t *state, void *user_data);
#define TD_LAYR TD(TD_LAYER_TOGGLE)
#endif // TAP_DANCE_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Keymap expansions
///////////////////////////////////////////////////////////////////////////////

// Another idea shamelessly copied from Drashna.
// This allows me to keep some of my outer layers standardized between multiple
// keyboards as I make changes to them.

// Note that in orded to use these, you need to use the LAYOUT_wrapper functions
// defined here, not the normal LAYOUT functions.

#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)

#define _________________L_COLEMAK_L1______________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define _________________L_COLEMAK_L2______________       KC_A,    KC_R_LT, KC_S_LT, KC_T,    KC_G
#define _________________L_COLEMAK_L3______________       KC_Z,    KC_X,    KC_C,    KC_D_LT, KC_V

#define _________________L_COLEMAK_R1______________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________L_COLEMAK_R2______________       KC_M,    KC_N,    KC_E_LT, KC_I_LT, KC_O
#define _________________L_COLEMAK_R3______________       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH



#define _________________L_QWERTY_L1_______________       KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T
#define _________________L_QWERTY_L2_______________       KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G
#define _________________L_QWERTY_L3_______________       KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B

#define _________________L_QWERTY_R1_______________       KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P
#define _________________L_QWERTY_R2_______________       KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN
#define _________________L_QWERTY_R3_______________       KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH



#define _________________L_EXTEND_L1_______________       _______, _______, KC_APP,  KX_CGR,  KX_PAST
#define _________________L_EXTEND_L2_______________       KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, _______
#define _________________L_EXTEND_L3_______________       _______, _______, _______, KX_SRCH, KX_ARSC

#define _________________L_EXTEND_R1_______________       KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL
#define _________________L_EXTEND_R2_______________       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC
#define _________________L_EXTEND_R3_______________       _______, KX_STAB, KC_TAB,  KX_WTAB, KC_INS



#define __________________L_LL_R_L1________________       _______, _______, _______, _______, _______
#define __________________L_LL_R_L2________________       _______, ooooooo, KC_AMPR, KC_PIPE, _______
#define __________________L_LL_R_L3________________       _______, _______, _______, _______, _______

#define __________________L_LL_R_R1________________       KC_COLN, KC_7,    KC_8,    KC_9,    KC_PSLS
#define __________________L_LL_R_R2________________       KC_HASH, KC_4,    KC_5,    KC_6,    KC_PAST
#define __________________L_LL_R_R3________________       KC_BSPC, KC_1,    KC_2,    KC_3,    KC_PMNS



#define __________________L_LL_S_L1________________       _______, _______, _______, _______, _______
#define __________________L_LL_S_L2________________       _______, _______, ooooooo, _______, _______
#define __________________L_LL_S_L3________________       _______, _______, _______, _______, _______

#define __________________L_LL_S_R1________________       KC_VOLU, KC_F9,   KC_F10,  KC_F11,  KC_F12
#define __________________L_LL_S_R2________________       KC_MUTE, KC_F5,   KC_F6,   KC_F7,   KC_F8
#define __________________L_LL_S_R3________________       KC_VOLD, KC_F1,   KC_F2,   KC_F3,   KC_F4



#define __________________L_LL_E_L1________________       _______, _______, RJ_SELS, RJ_DUND, _______
#define __________________L_LL_E_L2________________       RJ_NEQ,  RJ_EQ,   RJ_LEQ,  RJ_GEQ,  RJ_GEQR
#define __________________L_LL_E_L3________________       _______, _______, _______, _______, _______

#define __________________L_LL_E_R1________________       _______, _______, _______, _______, RJ_QMKV
#define __________________L_LL_E_R2________________       _______, _______, ooooooo, _______, RJ_MAKE
#define __________________L_LL_E_R3________________       _______, _______, _______, _______, _______



#define __________________L_LL_I_L1________________       KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_SLSH
#define __________________L_LL_I_L2________________       KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_PIPE
#define __________________L_LL_I_L3________________       KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLS

#define __________________L_LL_I_R1________________       _______, KC_UNDS, KC_GRV,  _______, _______
#define __________________L_LL_I_R2________________       _______, KC_MINS, KC_QUOT, ooooooo, _______
#define __________________L_LL_I_R3________________       _______, KC_TILD, KC_DQT,  _______, _______

