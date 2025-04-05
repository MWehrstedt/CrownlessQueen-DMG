#ifndef __MOVES_H__
#define __MOVES_H__
#include "types.h"

/// @brief Handles inputs on main menu screen
void heroInputs(void) NONBANKED;

extern const move_t heroMoveFrames[4];
BANKREF_EXTERN(heroMoveFrames)

extern const int8_t heroMoveHitboxOffsetXRight[4];
BANKREF_EXTERN(heroMoveHitboxOffsetXRight)

extern const int8_t heroMoveHitboxOffsetXLeft[4];
BANKREF_EXTERN(heroMoveHitboxOffsetXLeft)

extern const int8_t heroMoveHitboxOffsetY[4];
BANKREF_EXTERN(heroMoveHitboxOffsetY)

extern const int8_t heroMoveHitboxWidth[4];
BANKREF_EXTERN(heroMoveHitboxWidth)

extern const int8_t heroMoveHitboxHeight[4];
BANKREF_EXTERN(heroMoveHitboxHeight)
#endif