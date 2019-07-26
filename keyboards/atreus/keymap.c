#include QMK_KEYBOARD_H
#include "version.h"

// Layers
enum atreus_replicaJunction_layers {
  L_BASE,
  L_LOWER,
  L_RAISE,
  L_ADJUST,
  L_MACRO,
  L_MOUSE
};

enum atreus_replicaJunction_keycodes {
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

#define KC_SFTAB LSFT(KC_TAB)
#define KC_WTAB  LGUI(KC_TAB)

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

// Application-specific shortcuts

#define M_CONSOL LCTL(KC_GRV)
#define M_SEARCH LCTL(LGUI(LALT(KC_S)))

//----------------------------------------------------------------------
// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT(
    KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,                  KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,
    KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G    ,                  KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,
    KC_Z    ,KC_X    ,KC_C    ,KC_D_LT ,KC_V    ,                  KC_K    ,KC_H_LT ,KC_COMM ,KC_DOT  ,KC_SLSH ,
    KC_ESC  ,KC_LGUI ,KC_TAB  ,KC_LSFT ,KC_BS_LT,KC_DEL_C,KC_ENT_A,KC_SP_LT,KC_RSFT ,KC_MINS ,KC_QUOT ,KC_EQL
  ),

  [L_LOWER] = LAYOUT(
    KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,                  ________,KC_7    ,KC_8    ,KC_9    ,KC_ASTR ,
    KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV  ,                  ________,KC_4    ,KC_5    ,KC_6    ,KC_PIPE ,
    KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,                  KC_AMPR ,KC_1    ,KC_2    ,KC_3    ,KC_BSLS ,
    ________,________,________,________,oooooooo,________,KC_ENT  ,oooooooo,KC_0    ,KC_DOT  ,KC_EQL  ,________
  ),

  [L_RAISE] = LAYOUT(
    ________,________,________,M_CONSOL,________,                  KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_DEL  ,
    KC_LGUI ,KC_LSFT ,KC_LALT ,KC_LCTL ,________,                  KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_BSPC ,
    ________,________,________,M_SEARCH,________,                  ________,KC_SFTAB,KC_TAB  ,KC_WTAB ,KC_PSCR ,
    ________,________,________,________,oooooooo,________,________,oooooooo,________,________,________,________
  ),

  [L_ADJUST] = LAYOUT(
    RESET   ,________,________,KC_INS  ,KC_NLCK ,                  KC_WFWD ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,
    ________,________,D_PLAY2 ,D_PLAY1 ,________,                  KC_WBAK ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,
    ________,________,D_REC2  ,D_REC1  ,D_STOP  ,                  ________,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,
    ________,________,________,________,oooooooo,________,________,oooooooo,________,________,________,________
  ),

  [L_MACRO] = LAYOUT(
    ________,________,________,________,________,                  ________,________,________,________,________,
    ________,________,________,________,________,                  ________,________,________,________,________,
    ________,________,________,oooooooo,________,                  ________,________,________,________,________,
    ________,________,________,________,________,________,________,________,________,________,________,________
  ),

  // Mouse keys
  [L_MOUSE] = LAYOUT(
    ________,________,KC_MS_U ,________,KC_WH_U ,                  ________,________,________,________,________,
    ________,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,                  ________,________,________,________,________,
    ________,________,________,________,________,                  ________,oooooooo,________,________,________,
    ________,________,________,KC_BTN3 ,KC_BTN1 ,KC_BTN2 ,________,________,________,________,________,________
  )

  // Template
  // [L_NAME] = LAYOUT(
  //   ________,________,________,________,________,                  ________,________,________,________,________,
  //   ________,________,________,________,________,                  ________,________,________,________,________,
  //   ________,________,________,________,________,                  ________,________,________,________,________,
  //   ________,________,________,________,________,________,________,________,________,________,________,________
  // ),
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