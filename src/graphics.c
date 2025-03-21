#include <gbdk/platform.h>
#include <gbdk/gbdecompress.h>
#include <stdlib.h>
#include "../res/levelHero_tiles.h"
#include "../res/levelHero_map.h"
#include "../res/windowMap.h"
#include "../res/heroTiles.h"
#include "../res/windowTiles.h"

#include "animations.h"
#include "graphics.h"
#include "vars.h"

#pragma bank 255

BANKREF(initGfxMainMenu)
void initGfxMainMenu(void) BANKED
{
    uint8_t buffer[4096];

    // Load decompressed tiles into bkg
    set_bkg_data(0, gb_decompress(levelHero_tiles, buffer) >> 4, buffer);

    // Load decompressed tiles into window
#if defined(GAMEBOY)
    set_win_data(100, gb_decompress(windowTiles, buffer) >> 4, buffer);
#endif

    // Load decompressed tiles into spr
    set_sprite_data(1, gb_decompress(heroTiles, buffer) >> 4, buffer);
    set_sprite_data(70, gb_decompress(heroTiles, buffer) >> 4, buffer);

    // Set bkg map
    set_bkg_tiles(0, 0, 20u, 14u, levelHero_map);

#if defined(GAMEBOY)
    // Set wnd map
    set_win_tiles(0, 0, 20u, 8u, windowMap);

    // Set wnd position
    move_win(7, 112);
#endif

    // Set hero and enemy tiles
    for (iterator = 0; iterator < 12; ++iterator)
    {
        set_sprite_tile(OAM_HERO_SPRITEID + iterator, heroIdleFrames[0][iterator]);
    }

    for (iterator = 0; iterator < 9; ++iterator)
    {
        set_sprite_tile(OAM_ENEMY_SPRITEID + iterator, bossDbgFrames[0][iterator]);
    }

    free(buffer);

    // DEBUG: assign hitbox sprites
    set_sprite_tile(12, 64);
    set_sprite_tile(30, 64);

    // Turn the on visible layers to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
#if defined(GAMEBOY)
    SHOW_WIN;
#endif
    DISPLAY_ON;
}

BANKREF_EXTERN(updateHealthBar)
void updateHealthBar(void) BANKED
{

    if (currentObject->maxHealth == 20)
    {
        for (iterator = 0; iterator < 5; ++iterator)
        {
            if (currentObject->health > 3 + (iterator * 4))
            {
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID + 4);
            }
            else if (currentObject->health <= iterator * 4)
            {
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID);
            }
            else
            {
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID + currentObject->health % 4);
            }
        }
    }
    else
    {
        for (iterator = 0; iterator < 8; ++iterator)
        {
            if (currentObject->health > 3 + (iterator * 4))
            {
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID + 4);
            }
            else if (currentObject->health <= iterator * 4)
            {
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID);
            }
            else
            {
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID + currentObject->health % 4);
            }
        }
    }
}
