#include <gbdk/platform.h>

#ifndef __HERO_H__
#define __HERO_H__

/// @brief Draw and animate hero sprite
void drawHero(void) NONBANKED;
BANKREF_EXTERN(drawHero)

/// @brief Initialize hero
void initHero(void) NONBANKED;
BANKREF_EXTERN(initHero)

/// @brief Handles inputs on main menu screen
void heroInputs(void) NONBANKED;

void drawHitbox(void) BANKED;
BANKREF_EXTERN(drawHitbox)

/// @brief Main hero routine
void updateHero(void) NONBANKED;
BANKREF_EXTERN(updateHero)

void updateHitbox(void) BANKED;
BANKREF_EXTERN(updateHitbox)

void setupMove(void) BANKED;
BANKREF_EXTERN(setupMove)

/// @brief Main weapon routine
void updateWeapon(void) BANKED;
BANKREF_EXTERN(updateWeapon)

#endif