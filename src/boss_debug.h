#include <gbdk/platform.h>

#ifndef __BOSS_DEBUG_H__
#define __BOSS_DEBUG_H__

/// @brief Draw and animate boss sprite
void drawBossDbg(void) NONBANKED;
BANKREF_EXTERN(drawBossDbg)

/// @brief Initialize boss
void initBossDbg(void) NONBANKED;
BANKREF_EXTERN(initBossDbg)

/// @brief Handles boss inputs
void bossDbgInputs(void) NONBANKED;
BANKREF_EXTERN(bossDbgInputs)

/// @brief Main boss routine
void updateBossDbg(void) NONBANKED;
BANKREF_EXTERN(updateBossDbg)

#endif