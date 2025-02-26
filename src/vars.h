#ifndef __VARS_H__
#define __VARS_H__
#include <gbdk/platform.h>
#include "types.h"

extern character_t hero;
BANKREF_EXTERN(hero)

extern character_t enemy;
BANKREF_EXTERN(enemy)

extern game_t game;
BANKREF_EXTERN(game)

extern character_t *currentObject;
BANKREF_EXTERN(currentObject)

extern hitbox_t heroAttackHitbox;
BANKREF_EXTERN(heroAttackHitbox)

/// @brief Inputs for current frame for player 1
extern uint8_t joypadCurrent;
BANKREF_EXTERN(joypadCurrent)

/// @brief Inputs for last frame for player 1
extern uint8_t joypadPrevious;
BANKREF_EXTERN(joypadPrevious)

/// @brief Inputs for current frame for player 2
extern uint8_t joypadCurrent2;
BANKREF_EXTERN(joypadCurrent2)

/// @brief Inputs for last frame for player 2
extern uint8_t joypadPrevious2;
BANKREF_EXTERN(joypadPrevious2)

/// @brief Current joypad buffer for player 1
extern uint8_t *currentJoypad;
BANKREF_EXTERN(currentJoypad)

/// @brief Current joypad buffer for player 2
extern uint8_t *currentPreviousJoypad;
BANKREF_EXTERN(currentPreviousJoypad)

/// @brief Collision tile horizontal
extern targetTile_t targetTileHorizontal;

/// @brief Collision tile vertical
extern targetTile_t targetTileVertical;

/// @brief Scroll X offset
extern uint8_t scrollX;



#endif // !__VARS_H__
