#include <gbdk/platform.h>
#include "types.h"

#pragma bank 255

const move_t heroMoveFrames[4] = {
    {0, 1, 15 - 4, 7, 15},  // Jab
    {1, 5, 50 - 3, 44, 50}, // Uppercut
    {2, 2, 16 - 4, 10, 16}, // Side Step
    {3, 0, 30 - 1, 5, 30},  // Dash
};
BANKREF(heroMoveFrames)

// const uint8_t heroMoveHitboxesX[4] = {
//     {0, 1, 15 - 4, 7, 15},  // Jab
//     {1, 5, 50 - 3, 44, 50}, // Uppercut
//     {2, 2, 16 - 4, 10, 16}, // Side Step
//     {3, 0, 30 - 1, 5, 30},  // Dash
// };
// BANKREF(heroMoveHitboxes)
