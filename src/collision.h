#include <gbdk/platform.h>
#include "../include/stdbool.h"

#ifndef __COLLISION_H__
#define __COLLISION_H__

/// @brief Handle hero collisions with current level hitmaps
void getCollisions(void) BANKED;
BANKREF_EXTERN(getCollisions)

/// @brief Get tile from current hitmap based on position. Sets `targetTileLeft`, `targetTileRight`, `targetTileUp` and `targetTileDown` based on directions given.
void checkCollisionBackgroundX(void) BANKED;
BANKREF_EXTERN(checkCollisionBackgroundX)

/// @brief Get tile from current hitmap based on position. Sets `targetTileLeft`, `targetTileRight`, `targetTileUp` and `targetTileDown` based on directions given.
void checkCollisionBackgroundY(void) BANKED;
BANKREF_EXTERN(checkCollisionBackgroundY)

bool checkCollisionObject(void) BANKED;
BANKREF_EXTERN(checkCollisionObject)

bool checkCollisionHitbox(void) BANKED;
BANKREF_EXTERN(checkCollisionHitbox)
#endif