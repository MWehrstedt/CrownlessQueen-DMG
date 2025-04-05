#include <gbdk/platform.h>
#include "types.h"

#pragma bank 255

const move_t heroMoveFrames[4] = {
    {0, 1, 20 - 4, 11, 20},  // Jab
    {1, 5, 41 - 3, 33, 41}, // Uppercut
    {2, 2, 16 - 4, 10, 16}, // Side Step
    {3, 0, 30 - 1, 5, 30},  // Dash
};
BANKREF(heroMoveFrames)

const int8_t heroMoveHitboxOffsetXRight[4] = {
    20, 14, 20, 20,
};
BANKREF(heroMoveHitboxOffsetXRight)

const int8_t heroMoveHitboxOffsetXLeft[4] = {
    -3, -2, -3, -3,
};
BANKREF(heroMoveHitboxOffsetXLeft)

const int8_t heroMoveHitboxOffsetY[4] = {
    16, -4, 16, 16,
};
BANKREF(heroMoveHitboxOffsetY)

const int8_t heroMoveHitboxWidth[4] = {
    10, 13, 10, 10,
};
BANKREF(heroMoveHitboxWidth)

const int8_t heroMoveHitboxHeight[4] = {
    10, 32, 10, 10,
};
BANKREF(heroMoveHitboxHeight)