#include <gbdk/platform.h>

#ifndef __HERO_H__
#define __HERO_H__

/// @brief Draw and animate hero sprite
void drawHero(void) BANKED;
BANKREF_EXTERN(drawHero)

/// @brief Main hero routine
void updateHero(void) BANKED;
BANKREF_EXTERN(updateHero)

/// @brief Handle knockback during hitstate
void handleHitstate(void) BANKED;
BANKREF_EXTERN(handleHitstate)

/// @brief Main weapon routine
void updateWeapon(void) BANKED;
BANKREF_EXTERN(updateWeapon)
#endif