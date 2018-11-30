#pragma once

enum vim_keycodes {
    VIM_START = SAFE_RANGE, // bookend for vim states
    VIM_A,
    VIM_B,
    VIM_C,
    VIM_CI,
    VIM_D,
    VIM_DI,
    VIM_E,
    VIM_H,
    VIM_G,
    VIM_I,
    VIM_J,
    VIM_K,
    VIM_L,
    VIM_O,
    VIM_P,
    VIM_S,
    VIM_U,
    VIM_V,
    VIM_VS, // visual-line
    VIM_VI,
    VIM_W,
    VIM_X,
    VIM_Y,
    VIM_PERIOD, // to support indent/outdent
    VIM_COMMA,  // and toggle comments
    VIM_SHIFT, // avoid side-effect of supporting real shift.
    VIM_ESC, // bookend

    VIM_SAFE_RANGE // start other keycodes here.
};

// Convenient aliases for keymap definitions
#define V_START VIM_START
#define V_SHIFT VIM_SHIFT
#define V_DOT   VIM_PERIOD
#define V_COMMA VIM_COMMA

// NOTE: YOU MUST DEFINE THIS
extern uint8_t vim_cmd_layer(void);

bool process_record_vim(uint16_t keycode, keyrecord_t *record);

extern uint16_t vstate;


// Colemak base layer

#define __________________COLEMAK_L1_VIM___________       _______, VIM_W,   _______, VIM_P,   VIM_B
#define __________________COLEMAK_L2_VIM___________       VIM_A,   _______, VIM_S,   _______, VIM_G
#define __________________COLEMAK_L3_VIM___________       _______, _______, VIM_C,   VIM_D,   VIM_V

#define __________________COLEMAK_R1_VIM___________       VIM_J,   VIM_L,   VIM_U,   VIM_Y,   _______
#define __________________COLEMAK_R2_VIM___________       _______, _______, VIM_E,   VIM_I,   VIM_O
#define __________________COLEMAK_R3_VIM___________       VIM_K,   VIM_H,   VIM_DOT, VIM_COM, _______
