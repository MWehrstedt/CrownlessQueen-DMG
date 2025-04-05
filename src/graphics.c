#include <gbdk/platform.h>
#include <gbdk/gbdecompress.h>
#include <stdlib.h>
#if defined(GAMEBOY)
#include "../res/gb/levelHero_map-gb.h"
#include "../res/gb/levelHero_tiles-gb.h"
#include "../res/gb/heroTiles-gb.h"
#include "../res/gb/bossDbgTiles.h"
#include "../res/gb/windowTiles.h"
#elif defined(GAMEGEAR)
#include "../res/gg/levelHero_tiles-gg.h"
#include "../res/gg/heroTiles-gg.h"
#include "../res/gg/heroTiles-gg-left.h"
#include "../res/gg/bossDbg-Tiles-gg.h"
#include "../res/gg/win-tiles-gg.h"

#endif
#include "../res/windowMap.h"
#include "animations.h"
#include "graphics.h"
#include "vars.h"

#pragma bank 2

BANKREF(initGfxMainMenu)
void initGfxMainMenu(void) BANKED
{

#if defined(GAMEBOY)
    /*
        Load tile data in DMG format
    */
    uint8_t buffer[4096];

    // Load decompressed tiles into bkg
    set_bkg_data(0, gb_decompress(levelHero_tiles, buffer) >> 4, buffer);

    // Load decompressed tiles into window
    set_win_data(100, gb_decompress(windowTiles, buffer) >> 4, buffer);

    // Set wnd map
    set_win_tiles(0, 0, 20u, 8u, windowMap);

    // Set wnd position
    move_win(7, 112);

    // Load decompressed tiles into spr
    set_sprite_data(1, gb_decompress(heroTiles_tiles, buffer) >> 4, buffer);
    set_sprite_data(70, gb_decompress(bossDbgTiles, buffer) >> 4, buffer);

    free(buffer);

    // Set bkg map
    set_bkg_tiles(0, 0, 20u, 14u, levelHero_map);

#elif defined(GAMEGEAR)
    /*
        Load tile data in GG format
    */

    // Set bkg tiles
    set_palette(0, 1, levelHero_tiles_gg_palettes);
    set_native_tile_data(0, levelHero_tiles_gg_TILE_COUNT, levelHero_tiles_gg_tiles);

    // Set wnd tiles
    set_native_tile_data(100, win_tiles_gg_TILE_COUNT, win_tiles_gg_tiles);

    set_palette(1, 1, heroTiles_gg_palettes);
    set_sprite_4bpp_data(1, heroTiles_gg_TILE_COUNT, heroTiles_gg_tiles);
    set_sprite_4bpp_data(70, bossDbg_Tiles_gg_TILE_COUNT, bossDbg_Tiles_gg_tiles);

    set_bkg_tiles(0, 0, 20u, 14u, levelHero_tiles_gg_map);
    set_bkg_tiles(0, 14, 20u, 4u, windowMap);

#endif

    // Set hero and enemy tiles
    for (iterator = 0; iterator < 12; ++iterator)
    {
        set_sprite_tile(OAM_HERO_SPRITEID + iterator, 0);
    }

    for (iterator = 0; iterator < 9; ++iterator)
    {
        set_sprite_tile(OAM_ENEMY_SPRITEID + iterator, 0);
    }

    // DEBUG: assign hitbox sprites
    set_sprite_tile(12, 64);
    set_sprite_tile(30, 65);

    move_sprite(30, 48 + DEVICE_SPRITE_PX_OFFSET_X, 120 + DEVICE_SPRITE_PX_OFFSET_Y);

    // Turn the on visible layers to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
#if defined(GAMEBOY)
    SHOW_WIN;
#endif
    DISPLAY_ON;
}

BANKREF(updateHealthBar)
void updateHealthBar(void) BANKED
{

    if (currentObject->maxHealth == 20)
    {
        for (iterator = 0; iterator < 5; ++iterator)
        {
            if (currentObject->health > 3 + (iterator * 4))
            {
#if defined(GAMEBOY)
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID + 4);
#else
                set_bkg_tile_xy(1 + iterator, 16, WND_BLANK_TILE_ID + 4);
#endif
            }
            else if (currentObject->health <= iterator * 4)
            {
#if defined(GAMEBOY)
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID);
#else
                set_bkg_tile_xy(1 + iterator, 16, WND_BLANK_TILE_ID);
#endif
            }
            else
            {
#if defined(GAMEBOY)
                set_win_tile_xy(1 + iterator, 2, WND_BLANK_TILE_ID + currentObject->health % 4);
#else
                set_bkg_tile_xy(1 + iterator, 16, WND_BLANK_TILE_ID + currentObject->health % 4);
#endif
            }
        }
    }
    else
    {
        for (iterator = 0; iterator < 8; ++iterator)
        {
            if (currentObject->health > 3 + (iterator * 4))
            {
#if defined(GAMEBOY)
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID + 4);
#else
                set_bkg_tile_xy(11 + iterator, 16, WND_BLANK_TILE_ID + 4);
#endif
            }
            else if (currentObject->health <= iterator * 4)
            {
#if defined(GAMEBOY)
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID);
#else
                set_bkg_tile_xy(11 + iterator, 16, WND_BLANK_TILE_ID);
#endif
            }
            else
            {
#if defined(GAMEBOY)
                set_win_tile_xy(11 + iterator, 2, WND_BLANK_TILE_ID + currentObject->health % 4);
#else
                set_bkg_tile_xy(11 + iterator, 16, WND_BLANK_TILE_ID + currentObject->health % 4);
#endif
            }
        }
    }
}

BANKREF(loadPlayer1Sprites)
void loadPlayer1Sprites(void) BANKED
{
#if defined(GAMEBOY)
    /*
        Load tile data in DMG format
    */
    uint8_t buffer[4096];

    // Load decompressed tiles into spr
    set_sprite_data(1, gb_decompress(heroTiles_tiles, buffer) >> 4, buffer);

    free(buffer);
#elif defined(GAMEGEAR)
    /*
        Load tile data in GG format
    */

    set_palette(1, 1, heroTiles_gg_palettes);

    if (currentObject->direction == HERO_DIRECTION_RIGHT)
    {
        set_sprite_4bpp_data(1, heroTiles_gg_TILE_COUNT, heroTiles_gg_tiles);
    }
    else
    {
        set_sprite_4bpp_data(1, heroTiles_gg_TILE_COUNT, heroTiles_gg_left_tiles);
    }

#endif

    // Set hero tiles
    for (iterator = 0; iterator < 12; ++iterator)
    {
        set_sprite_tile(OAM_HERO_SPRITEID + iterator, 0);
    }
}

BANKREF(loadPlayer2Sprites)
void loadPlayer2Sprites(void) BANKED
{
    // #if defined(GAMEBOY)
    //     /*
    //         Load tile data in DMG format
    //     */
    //     uint8_t buffer[4096];

    //     // Load decompressed tiles into spr
    //     set_sprite_data(70, gb_decompress(bossDbgTiles, buffer) >> 4, buffer);

    //     free(buffer);
    // #elif defined(GAMEGEAR)
    //     /*
    //         Load tile data in GG format
    //     */

    //     set_palette(1, 1, heroTiles_gg_palettes);

    //     if (currentObject->direction == HERO_DIRECTION_RIGHT)
    //     {
    //         set_sprite_4bpp_data(1, heroTiles_gg_TILE_COUNT, heroTiles_gg_tiles);
    //     }
    //     else
    //     {
    //         set_sprite_4bpp_data(1, heroTiles_gg_TILE_COUNT, heroTiles_gg_left_tiles);
    //     }

    // #endif

    //     // Set ememy sprites
    //     for (iterator = 0; iterator < 9; ++iterator)
    //     {
    //         set_sprite_tile(OAM_ENEMY_SPRITEID + iterator, 0);
    //     }
}