#include <gbdk/platform.h>
#include "audio.h"
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

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        game.state = GAME_STATE_INITGAMEPLAY;
    }

    joypadPrevious = joypadCurrent;
}

/// @brief Handles inputs on main menu screen
void pauseInputs(void) NONBANKED
{
    joypadCurrent = joypad();

    if (joypadCurrent & J_RIGHT && !(joypadPrevious & J_RIGHT))
    {
        game.selectedMenuItem = (++game.selectedMenuItem % 2);
        playSFX(0);
    }

    if (joypadCurrent & J_LEFT && !(joypadPrevious & J_LEFT))
    {
        if (game.selectedMenuItem == 0)
        {
            game.selectedMenuItem = 1;
        }
        else
        {
            game.selectedMenuItem = 0;
        }
        playSFX(0);
    }

    // Update WIN Tile for menu
    if (!game.selectedMenuItem)
    {
        set_win_tile_xy(1, 6, 121);
        set_win_tile_xy(14, 6, 100);
    }
    else
    {
        set_win_tile_xy(1, 6, 100);
        set_win_tile_xy(14, 6, 121);
    }

    if (joypadCurrent & J_A && !(joypadPrevious & J_A))
    {
        if (!game.selectedMenuItem)
        {
            game.state = GAME_STATE_INITGAMEPLAY;
        }
        else
        {
            game.state = GAME_STATE_INTRO;
        }
    }

    if (joypadCurrent & J_START && !(joypadPrevious & J_START))
    {
        game.state = GAME_STATE_UNPAUSING;
    }

    joypadPrevious = joypadCurrent;
}
