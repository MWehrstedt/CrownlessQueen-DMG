#include <gbdk/platform.h>

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


void initGfxMainMenu(void) BANKED;
BANKREF_EXTERN(initGfxMainMenu)

void initGfxTraining(void) BANKED;
BANKREF_EXTERN(initGfxTraining)

void updateHealthBar(void) BANKED;
BANKREF_EXTERN(updateHealthBar)

void loadPlayer1Sprites(void) BANKED;
BANKREF_EXTERN(loadPlayer1Sprites)

void loadPlayer2Sprites(void) BANKED;
BANKREF_EXTERN(loadPlayer2Sprites)
#endif