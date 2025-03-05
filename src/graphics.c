#include <gbdk/platform.h>
#include <gbdk/gbdecompress.h>
#include "../res/debugTiles.h"
#include "../res/debugMap.h"
#include "animations.h"
#include "graphics.h"
#include "vars.h"

#pragma bank 255

uint8_t buffer[4096];

BANKREF(initGfxMainMenu)
void initGfxMainMenu(void) BANKED
{
    // Load decompressed tiles into bkg
    set_bkg_data(0, gb_decompress(debugTiles, buffer) >> 4, buffer);

    // Load decompressed tiles into bkg
    set_sprite_data(0, gb_decompress(debugTiles, buffer) >> 4, buffer);

    // Set map
    set_bkg_tiles(0, 0, 32u, 16u, debugMap);
    
    // Set hero and enemy tiles
    for (iterator = 0; iterator < 9; ++iterator)
    {
        set_sprite_tile(OAM_HERO_SPRITEID + iterator, heroIdleFrames[0][iterator]);
    }

    for (iterator = 0; iterator < 9; ++iterator)
    {
        set_sprite_tile(OAM_ENEMY_SPRITEID + iterator, bossDbgFrames[0][iterator]);
    }
    

    // set_sprite_tile(0, 1);
    // set_sprite_tile(1, 1);
    // set_sprite_tile(2, 1);
    // set_sprite_tile(3, 1);
    // set_sprite_tile(4, 1);
    // set_sprite_tile(5, 1);
    // set_sprite_tile(6, 1);
    // set_sprite_tile(7, 1);
    // set_sprite_tile(8, 1);
    // set_sprite_tile(9, 1);
    // set_sprite_tile(10, 1);
    // set_sprite_tile(11, 1);

    // set_sprite_tile(20, 2);
    // set_sprite_tile(21, 2);
    // set_sprite_tile(22, 2);
    // set_sprite_tile(23, 2);
    // set_sprite_tile(24, 2);
    // set_sprite_tile(25, 2);
    // set_sprite_tile(26, 2);
    // set_sprite_tile(27, 2);
    // set_sprite_tile(28, 2);

    // DEBUG: assign hitbox sprites
    set_sprite_tile(12, 2);
    set_sprite_tile(13, 2);

    // Turn the on visible layers to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    // SHOW_WIN
    DISPLAY_ON;
}
