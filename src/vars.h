#ifndef __VARS_H__
#define __VARS_H__
#include <gbdk/platform.h>
#include "types.h"

/// @brief Temporary variable, used for one-off operations
extern int8_t temp;
BANKREF_EXTERN(temp)

/// @brief Global level 1 iterator
extern uint8_t iterator;
BANKREF_EXTERN(iterator)

/// @brief Player 1
extern character_t hero;
BANKREF_EXTERN(hero)

/// @brief Enemy, player 2
extern character_t enemy;
BANKREF_EXTERN(enemy)

/// @brief Game state manager
extern game_t game;
BANKREF_EXTERN(game)

/// @brief Currently active character
extern character_t *currentObject;
BANKREF_EXTERN(currentObject)

/// @brief Player 1 attack hitbox
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

/// @brief Previous state for player 1
extern uint8_t previousState1;
BANKREF_EXTERN(previousState1)

/// @brief Previous state for player 2
extern uint8_t previousState2;
BANKREF_EXTERN(previousState2)

/// @brief Current previous state 
extern uint8_t *currentPreviousState;
BANKREF_EXTERN(currentPreviousState)

/// @brief Collision tile horizontal
extern targetTile_t targetTileHorizontal;

/// @brief Collision tile vertical
extern targetTile_t targetTileVertical;

/// @brief Scroll X offset
extern uint8_t scrollX;

/// @brief Player 1 attack hitbox
extern uint8_t sideStepCounter;
BANKREF_EXTERN(sideStepCounter)

#endif // !__VARS_H__
