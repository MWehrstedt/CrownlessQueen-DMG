#include <gbdk/platform.h>
#include <gb/gb.h>
#include <gb/gbdecompress.h>
#include "../res/debugTiles.h"
#include "../res/debugMap.h"
#include "graphics.h"

#pragma bank 255

BANKREF(initGfxMainMenu)
void initGfxMainMenu(void) BANKED
{
    DISPLAY_OFF;
    // Load Background tiles and then map
    gb_decompress_bkg_data(0, debugTiles);
    set_bkg_tiles(0, 0, 32u, 16u, debugMap);

    gb_decompress_sprite_data(0, debugTiles);

    // DEBUG: assign hero sprites
    set_sprite_tile(0, 1);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 1);
    set_sprite_tile(3, 1);
    set_sprite_tile(4, 1);
    set_sprite_tile(5, 1);

    // Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

