#include <gbdk/platform.h>
#include "vars.h"
#include "types.h"

#pragma bank 0

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

targetTile_t targetTileHorizontal;
BANKREF(targetTileHorizontal)

targetTile_t targetTileVertical;
BANKREF(targetTileVertical)

uint8_t scrollX;
