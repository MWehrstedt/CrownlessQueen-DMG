#include <gbdk/platform.h>
#include "hero.h"
#include "input.h"
#include "vars.h"

#pragma bank 255

/// @brief Handles inputs on main menu screen
void mainmenuInputs(void) NONBANKED
{
    joypadCurrent = joypad();

    // Check for global reset
    // if(joypadCurrent & (J_A & J_B & J_START & J_SELECT) && !(joypadPrevious & (J_A & J_B & J_START & J_SELECT)))
    // {
    //     reset();
    // }

    if(joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        game.state = GAME_STATE_INITGAMEPLAY;
    }

    joypadPrevious = joypadCurrent;
}
