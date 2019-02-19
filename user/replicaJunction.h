#pragma once

#include "quantum.h"
///////////////////////////////////////////////////////////////////////////////
// Layer definitions
///////////////////////////////////////////////////////////////////////////////

enum layers {
    L_BASE,

    #ifdef HAS_LAYER_QWERTY
    L_QWERTY,
    #endif

    L_NUM,
    L_SYMBOL,
    L_EXTEND,
    L_FUNCTION,

    #ifdef HAS_LAYER_GAMING
    L_GAMING,
    #endif

    L_MACRO
};

///////////////////////////////////////////////////////////////////////////////
// Keymap definitions
///////////////////////////////////////////////////////////////////////////////

// Keyboard aliases
#define _______ KC_TRNS
#define ooooooo KC_TRNS

#define TT_NUM  TT(L_NUM)

#define TG_GAME TG(L_GAMING)

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

#define ALT_F4 LALT(F4)
#define WIN_L  LGUI(KC_L)

#define KC_R_LT LT(L_FUNCTION, KC_R)
#define KC_S_LT LT(L_NUM, KC_S)
#define KC_E_LT LT(L_SYMBOL, KC_E)
#define KC_D_LT LT(L_MACRO, KC_D)

// "Macro" functions
enum userspace_custom_keycodes {
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

    // Used for dynamic macros
    DYNAMIC_MACRO_RANGE
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

// "Smart numbers"
// Define USE_NUMPAD to have these send numpad keycodes;
// otherwise, they'll send normal number codes, as if
// hitting the number rows.

#ifdef USE_NUMPAD
    #define KC_NUM1 KC_P1
    #define KC_NUM2 KC_P2
    #define KC_NUM3 KC_P3
    #define KC_NUM4 KC_P4
    #define KC_NUM5 KC_P5
    #define KC_NUM6 KC_P6
    #define KC_NUM7 KC_P7
    #define KC_NUM8 KC_P8
    #define KC_NUM9 KC_P9
    #define KC_NUM0 KC_P0
    #define KC_NUME KC_PENT
    #define KC_NUMP KC_PPLS
    #define KC_NUMM KC_PMNS
    #define KC_NUMA KC_PAST
    #define KC_NUMS KC_PSLS
    #define KC_NUMD KC_PDOT
    #define KC_NUMQ KC_PEQL
#else
    #define KC_NUM1 KC_1
    #define KC_NUM2 KC_2
    #define KC_NUM3 KC_3
    #define KC_NUM4 KC_4
    #define KC_NUM5 KC_5
    #define KC_NUM6 KC_6
    #define KC_NUM7 KC_7
    #define KC_NUM8 KC_8
    #define KC_NUM9 KC_9
    #define KC_NUM0 KC_0
    #define KC_NUME KC_ENT
    #define KC_NUMP KC_PLUS
    #define KC_NUMM KC_MINS
    #define KC_NUMA KC_ASTR
    #define KC_NUMS KC_SLSH
    #define KC_NUMD KC_DOT
    #define KC_NUMQ KC_EQL
#endif

// Tap Dance
#ifdef TAP_DANCE_ENABLE
    #define TD_LAYER_TOGGLE 0
    #define TD_MACRO        1
    extern void dance_layer(qk_tap_dance_state_t *state, void *user_data);
    #define TD_LAYR TD(TD_LAYER_TOGGLE)

    extern void dance_macro(qk_tap_dance_state_t *state, void *user_data);
    #define TD_MACR TD(TD_MACRO)
#endif // TAP_DANCE_ENABLE
