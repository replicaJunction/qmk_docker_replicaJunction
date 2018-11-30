#include QMK_KEYBOARD_H
#include "vim.h"

// Convenience aliases
#define PRESS(kc) register_code(kc);
#define RELEASE(kc) unregister_code(kc);

static void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

static void CTRL(uint16_t keycode) {
  PRESS(KC_LCTRL);
    TAP(keycode);
  RELEASE(KC_LCTRL);
}

static void SHIFT(uint16_t keycode) {
  PRESS(KC_LSHIFT);
    TAP(keycode);
  RELEASE(KC_LSHIFT);
}

// These two are currently unused

// static void ALT(uint16_t keycode) {
//   PRESS(KC_LALT);
//     TAP(keycode);
//   RELEASE(KC_LALT);
// }

// static void GUI(uint16_t keycode) {
//   PRESS(KC_LGUI);
//     TAP(keycode);
//   RELEASE(KC_LGUI);
// }

uint16_t vstate = VIM_START;
static bool yank_was_lines = false;
static bool SHIFTED = false;
static uint32_t mod_override_layer_state = 0;
static uint16_t mod_override_triggering_key = 0;

// Use this command to enter "insert mode." In this case, that just
// clears the Vim layer completely.
static void edit(void) { vstate = VIM_START; layer_clear(); }
#define VIM_EDIT edit()

// Define these to make it easier to change OSes later if necessary
#define OS_UNDO  CTRL(KC_Z);
#define OS_CUT   CTRL(KC_X);
#define OS_COPY  CTRL(KC_C);
#define OS_PASTE CTRL(KC_V);

#define OS_START_LINE TAP(KC_HOME);
#define OS_END_LINE   TAP(KC_END);

static void simple_movement(uint16_t keycode) {
    switch(keycode) {
        case VIM_B:
            // b: cursor to beginning of word
            // Ctrl+Shift+Left on Windows
            // Alt+Shift+Left on OSX
            PRESS(KC_LCTRL);
                SHIFT(KC_LEFT);
            RELEASE(KC_LCTRL);
            break;

        case VIM_E:
            // e: cursor to end of word
            // Ctrl+Shift+Right on Windows
            PRESS(KC_LCTRL);
                SHIFT(KC_RIGHT);
            RELEASE(KC_LCTRL);
            break;

        case VIM_H:
            // h: left a character
            SHIFT(KC_LEFT);
            break;

        case VIM_J:
            // j: down a line
            OS_START_LINE;
            SHIFT(KC_DOWN);
            SHIFT(KC_DOWN);
            break;

        case VIM_K:
            // k: up a line
            OS_START_LINE;
            TAP(KC_DOWN);
            SHIFT(KC_UP);
            SHIFT(KC_UP);
            break;

        case VIM_L:
            // l: right a character
            SHIFT(KC_RIGHT);
            break;

        case VIM_W:
            // w: cursor to start of next word
            // Best way to do this on Windows is Ctrl+Shift+Right,Right,Left
            // (selects the next word, then deselects to the beginning)
            PRESS(KC_LCTRL);
                SHIFT(KC_RIGHT); // select to end of current word
                SHIFT(KC_RIGHT); // select to end of the next word
                SHIFT(KC_LEFT);  // deselect next word
            RELEASE(KC_LCTRL);

            break;
    }
}


// Call this from within process_record_user
bool process_record_vim(uint16_t keycode, keyrecord_t *record) {
    // Ignore if this isn't a Vim keycode
    if (keycode < VIM_START || VIM_ESC < keycode)
        return true;

    // Mod passthrough
    if (record->event.pressed && layer_state_is(vim_cmd_layer()) && (IS_MOD(keycode) || keycode == LSFT(KC_LALT))) {
        mod_override_layer_state = layer_state;
        mod_override_triggering_key = keycode;
        // TODO: change this to track key location instead
        layer_clear();
        return true; // let the event fall through...
    }

    if (mod_override_layer_state && !record->event.pressed && keycode == mod_override_triggering_key) {
        layer_state_set(mod_override_layer_state);
        mod_override_layer_state = 0;
        mod_override_triggering_key = 0;
        return true;
    }

    // If we pressed the Shift key, update the Vim Shift register and quit
    if (keycode == VIM_SHIFT) {
        SHIFTED = record->event.pressed;
        return false;
    }

    if (keycode == VIM_START) {
        layer_on(vim_cmd_layer());
        vstate = VIM_START;

        // Reset Vim state
        yank_was_lines = false;
        SHIFTED = false;
        mod_override_layer_state = 0;
        mod_override_triggering_key = 0;

        return false;
    }

    if (!record->event.pressed) {
        clear_keyboard();
        return false;
    }

    switch(vstate) {
        case VIM_START:
            // Start of command
            switch(keycode) {
                case VIM_A:
                    if (SHIFTED) {
                        // A - append at end of line
                        OS_END_LINE;
                    }
                    else {
                        // a - append after cursor
                        TAP(KC_RIGHT);
                    }
                    VIM_EDIT;
                    break;
                case VIM_B:
                    CTRL(KC_LEFT);
                    break;
                case VIM_C:
                    if (SHIFTED) {
                        // C - change line
                        OS_START_LINE;
                        SHIFT(KC_END);
                        OS_CUT;
                        yank_was_lines = false;
                        VIM_EDIT;
                    }
                    else {
                        // c - start of "change" command
                        vstate = VIM_C;
                    }
                    break;
                case VIM_D:
                    if (SHIFTED) {
                        // D - delete till end of line
                        SHIFT(KC_END);
                        OS_CUT;
                    }
                    else {
                        // d - start of "delete" command
                        vstate = VIM_D;
                    }
                    break;
                case VIM_E:
                    // e - end of current word
                    CTRL(KC_RIGHT);
                    break;
                case VIM_G:
                    if (SHIFTED) {
                        // G - go to bottom of document
                        CTRL(KC_END);
                    }
                    else {
                        // g - start of "goto" command
                        vstate = VIM_G;
                    }
                    break;
                case VIM_H:
                    PRESS(KC_LEFT);
                    break;
                case VIM_I:
                    if (SHIFTED) {
                        // I - insert at beginning of line
                        OS_START_LINE;
                    }
                    VIM_EDIT;
                    break;
                case VIM_J:
                    if (SHIFTED) {
                        // J - join lines
                        OS_START_LINE;
                        TAP(KC_DEL);
                    }
                    else {
                        // j - move down
                        PRESS(KC_DOWN);
                    }
                    break;
                case VIM_K:
                    PRESS(KC_UP);
                    break;
                case VIM_L:
                    PRESS(KC_RIGHT);
                    break;
                case VIM_O:
                    if (SHIFTED) {
                        // O - open a new line above current
                        OS_START_LINE;
                        TAP(KC_ENTER);
                        TAP(KC_UP);
                    }
                    else {
                        // o - open a new line after current
                        OS_END_LINE;
                        TAP(KC_ENTER);
                    }
                    VIM_EDIT;
                    break;
                case VIM_P:
                    if (SHIFTED) {
                        // P - paste above current line
                        OS_START_LINE;
                        OS_PASTE;
                    }
                    else {
                        // p - paste at current position
                        // Note the different handling of line yank
                        if (yank_was_lines) {
                            OS_END_LINE;
                            TAP(KC_RIGHT);
                        }
                        OS_PASTE;
                    }
                    break;
                case VIM_U:
                    // Windows doesn't have an easy way to support U
                    OS_UNDO;
                    break;
                case VIM_V:
                    if (SHIFTED) {
                        // V - visual line
                        OS_START_LINE;
                        SHIFT(KC_DOWN);
                        vstate = VIM_VS;
                    }
                    else {
                        // v - visual
                        vstate = VIM_V;
                    }
                    break;
                case VIM_W:
                    // w - cursor to start of next word
                    PRESS(KC_LCTRL);
                        TAP(KC_RIGHT);
                        TAP(KC_RIGHT);
                        TAP(KC_LEFT);
                    RELEASE(KC_LCTRL);
                    break;
                case VIM_Y:
                    if (SHIFTED) {
                        // Y - yank line
                        OS_START_LINE;
                        SHIFT(KC_DOWN);
                        OS_PASTE;
                        TAP(KC_UP);
                        yank_was_lines = true;
                    }
                    else {
                        // y - start of "yank" command
                        vstate = VIM_Y;
                    }
                    break;
            }
            break;

        case VIM_C:
            // c-  ...command, for change
            switch(keycode) {
                case VIM_B:
                case VIM_E:
                case VIM_H:
                case VIM_J:
                case VIM_K:
                case VIM_L:
                case VIM_W:
                    simple_movement(keycode);
                    OS_CUT;
                    yank_was_lines = false;
                    VIM_EDIT;
                    break;

                case VIM_C:
                    // cc - change current line
                    OS_START_LINE;
                    SHIFT(KC_END);
                    OS_CUT;
                    yank_was_lines = false;
                    VIM_EDIT;
                    break;
                case VIM_I:
                    // ci - start of "change inner" command
                    vstate = VIM_CI;
                    break;
                default:
                    // Invalid c- command, so cancel
                    vstate = VIM_START;
                    break;
            }
            break;

        case VIM_CI:
            // ci- ...for change inner
            // Currently only ciw is supported, for change inner word
            switch(keycode) {
                case VIM_W:
                    PRESS(KC_LCTRL);
                        TAP(KC_LEFT);       // Move to start of word
                        SHIFT(KC_RIGHT);    // Select to end of word
                    RELEASE(KC_LCTRL);

                    OS_CUT;
                    yank_was_lines = false;
                    VIM_EDIT;

                    // No break here because we also clear state
                default:
                    vstate = VIM_START;
                    break;
            }
            break;

        case VIM_D:
            // d-  ...delete
            switch(keycode) {
                case VIM_B:
                case VIM_E:
                case VIM_H:
                case VIM_J:
                case VIM_K:
                case VIM_L:
                case VIM_W:
                    simple_movement(keycode);
                    OS_CUT;
                    yank_was_lines = false;
                    vstate = VIM_START;
                    break;

                case VIM_D:
                    // dd - delete line
                    OS_START_LINE;
                    SHIFT(KC_DOWN);
                    OS_CUT;
                    yank_was_lines = true;
                    vstate = VIM_START;
                    break;
                case VIM_I:
                    // di - start of "delete inner" command
                    vstate = VIM_DI;
                    break;
                default:
                    // Invalid delete command
                    vstate = VIM_START;
                    break;
            }
            break;

        case VIM_DI:
            // di- ...delete inner
            // Again, only diw is currently supported
            switch(keycode) {
                case VIM_W:
                    PRESS(KC_LCTRL);
                        TAP(KC_LEFT);       // Move to start of word
                        SHIFT(KC_RIGHT);    // Select to end of word
                    RELEASE(KC_LCTRL);

                    OS_CUT;
                    yank_was_lines = false;
                default:
                    vstate = VIM_START;
                    break;
            }
            break;

        case VIM_G:
            // g-  ...goto, and a few other random ones
            switch(keycode) {
                case VIM_G:
                    // gg - go to top
                    CTRL(KC_HOME);
            }
            // Any key in g- mode will exit back to normal mode
            vstate = VIM_START;
            break;

        case VIM_V:
            // Visual mode
            switch(keycode) {
                case VIM_D:
                case VIM_X:
                    // d or x in visual mode both remove the currently highlighted selection
                    OS_CUT;
                    yank_was_lines = false;
                    vstate = VIM_START;
                    break;
                case VIM_B:
                    PRESS(KC_LCTRL);
                    PRESS(KC_LSHIFT);
                    PRESS(KC_LEFT);
                    // Leave the keys open so key repeat can kick in if desired
                    break;
                case VIM_E:
                    PRESS(KC_LCTRL);
                    PRESS(KC_LSHIFT);
                    PRESS(KC_RIGHT);
                    // Leave the keys open so key repeat can kick in if desired
                    break;
                case VIM_H:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_LEFT);
                    break;
                case VIM_I:
                    // vi - start of "visual inner" command
                    vstate = VIM_VI;
                    break;
                case VIM_J:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_DOWN);
                    break;
                case VIM_K:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_UP);
                    break;
                case VIM_L:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_RIGHT);
                    break;
                case VIM_P:
                    // p in visual mode replaces the highlighted text with the clipboard / buffer
                    OS_PASTE;
                    vstate = VIM_START;
                    break;
                case VIM_W:
                    // We can't repeat this one because it takes some special handlin'.
                    // To use key repeat, use E instead.
                    PRESS(KC_LCTRL);
                        SHIFT(KC_RIGHT);
                        SHIFT(KC_RIGHT);
                        SHIFT(KC_LEFT);
                    RELEASE(KC_LCTRL);
                    break;
                case VIM_Y:
                    OS_COPY;
                    TAP(KC_RIGHT);
                    yank_was_lines = false;
                    vstate = VIM_START;
                    break;
                case VIM_V:
                case VIM_ESC:
                    // v and Esc in visual mode both cancel visual mode
                    TAP(KC_RIGHT);
                    vstate = VIM_START;
                    break;
                default:
                    // In visual mode, if we don't recognize the command, don't do anything
                    break;
            }
            break;

        case VIM_VI:
            // vi-  ...select inner
            switch(keycode) {
                case VIM_W:
                    PRESS(KC_LCTRL);
                        TAP(KC_LEFT);       // Move to start of word
                        SHIFT(KC_RIGHT);    // Select to end of word
                    RELEASE(KC_LCTRL);
                    vstate = VIM_V;
                default:
                    vstate = VIM_START;
                    break;
            }
            break;

        case VIM_VS:
            // Visual line
            switch(keycode) {
                case VIM_D:
                case VIM_X:
                    OS_CUT;
                    yank_was_lines = true;
                    vstate = VIM_START;
                    break;
                case VIM_J:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_DOWN);
                    break;
                case VIM_K:
                    PRESS(KC_LSHIFT);
                    PRESS(KC_UP);
                    break;
                case VIM_Y:
                    OS_COPY;
                    yank_was_lines = true;
                    TAP(KC_RIGHT);
                    vstate = VIM_START;
                    break;
                case VIM_P:
                    OS_PASTE;
                    vstate = VIM_START;
                    break;
                case VIM_V:
                case VIM_ESC:
                    // v and Esc in visual line mode both cancel visual mode
                    TAP(KC_RIGHT);
                    vstate = VIM_START;
                    break;
                default:
                    // In visual line mode, if we don't recognize the command, don't do anything
                    break;
            }
            break;
    }

    return false;
}