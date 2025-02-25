#ifndef __VARS_H__
#define __VARS_H__
#include <gbdk/platform.h>
#include "types.h"

extern character_t hero;
BANKREF_EXTERN(hero)

extern game_t game;
BANKREF_EXTERN(game)

extern hitbox_t heroAttackHitbox;
BANKREF_EXTERN(heroAttackHitbox)

/// @brief Inputs for current frame
extern uint8_t joypadCurrent;
BANKREF_EXTERN(joypadCurrent)

/// @brief Inputs for last frame
extern uint8_t joypadPrevious;
BANKREF_EXTERN(joypadPrevious)

/// @brief Collision tile horizontal
extern targetTile_t targetTileHorizontal;

/// @brief Collision tile vertical
extern targetTile_t targetTileVertical;


#endif // !__VARS_H__
