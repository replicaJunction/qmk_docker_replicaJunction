#pragma once

// Prevent modifiers from sticking when switching layers
// Uses 5 bytes of memory per 8 keys, but makes sure modifiers don't get "stuck" switching layers
#define PREVENT_STUCK_MODIFIERS

// MS the button needs to be held before a tap becomes a hold (default: 200)
// #undef TAPPING_TERM
// #define TAPPING_TERM    250

// Makes it easier for fast typists to use dual-role keys. See additional details here:
// https://docs.qmk.fm/features/advanced-keycodes#permissive-hold
#define PERMISSIVE_HOLD

// This makes it possible to do rolling combos (zx) with keys that convert to other keys on hold
// (for example, if z becomes ctrl when you hold it, when this option isn't enabled, z rapidly
// followed by x actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
