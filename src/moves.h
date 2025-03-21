#include <gbdk/platform.h>

#ifndef __MOVES_H__
#define __MOVES_H__
#include "types.h"

/// @brief Handles inputs on main menu screen
void heroInputs(void) NONBANKED;

static const move_t heroMoveFrames[4] = {
    {0, 1, 15 - 4, 7, 15},  // Jab
    {1, 5, 50 - 3, 36, 50}, // Uppercut
    {2, 2, 16 - 4, 10, 16}, // Side Step
    {3, 0, 30 - 1, 5, 30},  // Dash
};

#endif