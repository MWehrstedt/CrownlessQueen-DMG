#include <gbdk/platform.h>
#include "vars.h"
#include "types.h"

#pragma bank 0

int8_t temp;
BANKREF(temp)

uint8_t music_paused;
BANKREF(music_paused)

uint8_t iterator;
BANKREF(iterator)

character_t hero;
BANKREF(hero)

character_t enemy;
BANKREF(enemy)

character_t *currentObject;
BANKREF(currentObject)

game_t game;
BANKREF(game)

hitbox_t heroAttackHitbox;
BANKREF(heroAttackHitbox)

uint8_t joypadCurrent;
BANKREF(joypadCurrent)

uint8_t joypadPrevious;
BANKREF(joypadPrevious)

uint8_t joypadCurrent2;
BANKREF(joypadCurrent2)

uint8_t joypadPrevious2;
BANKREF(joypadPrevious2)

uint8_t *currentJoypad;
BANKREF(currentJoyPad)

uint8_t *currentPreviousJoypad;
BANKREF(currentPreviousJoypad)

uint8_t previousState1;
BANKREF(previousState1)

uint8_t previousState2;
BANKREF(previousState2)

uint8_t *currentPreviousState;
BANKREF(currentPreviousState)

uint8_t previousDirection1;
BANKREF(previousDirection1)

uint8_t previousDirection2;
BANKREF(previousDirection2)

// uint8_t *currentPreviousDirection;
// BANKREF(currentPreviousDirection)

targetTile_t targetTileHorizontal;
BANKREF(targetTileHorizontal)

targetTile_t targetTileVertical;
BANKREF(targetTileVertical)

uint8_t sideStepCounter;
BANKREF(sideStepCounter)
