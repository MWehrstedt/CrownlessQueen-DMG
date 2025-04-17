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

    if (joypadCurrent & J_DOWN && !(joypadPrevious & J_DOWN))
    {
        game.selectedMenuItem = (++game.selectedMenuItem % 2);
        playSFX(0);
    }

    if (joypadCurrent & J_UP && !(joypadPrevious & J_UP))
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

        game.selectedMenuItem = 0;
    }

    if ((joypadCurrent & J_START && !(joypadPrevious & J_START)) ||
        joypadCurrent & J_B && !(joypadPrevious & J_B))
    {
        game.state = GAME_STATE_UNPAUSING;
        game.selectedMenuItem = 0;
    }

    // Update WIN Tile for menu
    if (!game.selectedMenuItem)
    {
        set_win_tile_xy(6, 13, 121);
        set_win_tile_xy(6, 15, 100);
    }
    else
    {
        set_win_tile_xy(6, 13, 100);
        set_win_tile_xy(6, 15, 121);
    }

    joypadPrevious = joypadCurrent;
}
