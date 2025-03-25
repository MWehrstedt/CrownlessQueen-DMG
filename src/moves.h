#ifndef __MOVES_H__
#define __MOVES_H__
#include "types.h"

/// @brief Handles inputs on main menu screen
void heroInputs(void) NONBANKED;

extern const move_t heroMoveFrames[4];
BANKREF_EXTERN(heroMoveFrames)
#endif