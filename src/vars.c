#include <gb/gb.h>
#include <gbdk/platform.h>
#include "vars.h"
#include "types.h"

#pragma bank 0

hero_t hero;
BANKREF(hero)

uint8_t joypadCurrent;
BANKREF(joypadCurrent)

uint8_t joypadPrevious;
BANKREF(joypadPrevious)

targetTile_t targetTileHorizontal;
BANKREF(targetTileHorizontal)

targetTile_t targetTileVertical;
BANKREF(targetTileVertical)