#pragma once

// Layer definitions

#define L_COLEMAK  0
#define L_QWERTY   1
#define L_NUM      2
#define L_SYMBOL   3
#define L_EXTEND   4
#define L_FUNCTION 5
#define L_MACRO    6
#define L_GAMING   7

// These tell my userspace config which layers go on tap-hold letters

#define L_LL_R     L_FUNCTION
#define L_LL_S     L_NUM
#define L_LL_E     L_SYMBOL
#define L_LL_D     L_MACRO

// Tells replicaJunction.h to use numpad keycodes for the L_NUM layer

#define USE_NUMPAD
