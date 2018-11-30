#pragma once

// Layer definitions

#define L_COLEMAK  0
#define L_NUM      1
#define L_SYMBOL   2
#define L_EXTEND   3
#define L_FUNCTION 4
#define L_MACRO    5
#define L_VIM      6

// These tell my userspace config which layers go on tap-hold letters

#define L_LL_R     L_FUNCTION
#define L_LL_S     L_NUM
#define L_LL_E     L_SYMBOL
#define L_LL_D     L_MACRO

// Define the leader to be a bit longer, since the leader key on this
// keyboard is in a hard-to-reach location
#ifdef LEADER_TIMEOUT
    #undef LEADER_TIMEOUT
#endif
#define LEADER_TIMEOUT 500
