#include <gbdk/platform.h>
#include <stdint.h>
#include "graphics.h"
#include "collision.h"
#include "hero.h"
#include "boss_debug.h"
#include "input.h"
#include "vars.h"

#if defined(NINTENDO)
#include "sgb.h"
#include "../res/sgb_border.h"
#endif

void main(void)
{
#if defined(SEGA)
    __WRITE_VDP_REG(VDP_R2, R2_MAP_0x3800);
    __WRITE_VDP_REG(VDP_R5, R5_SAT_0x3F00);
#else

    // Wait 4 frames
    // For SGB on PAL SNES this delay is required on startup, otherwise borders don't show up
    for (iterator = 4; iterator != 0; iterator--)
        vsync();

    // The display must be ON before calling set_sgb_border()
    DISPLAY_ON;
    set_sgb_border(sgb_border_tiles,
                   sizeof(sgb_border_tiles),
                   sgb_border_map,
                   sizeof(sgb_border_map),
                   sgb_border_palettes, sizeof(sgb_border_palettes));
#endif

    initGfxMainMenu();

    initHero();
    initBossDbg();
    game.state = GAME_STATE_GAMEPLAY;

    game.selectedSpecials = HERO_ATTACK_UPPERCUT;

    // Loop forever
    while (1)
    {
        switch (game.state)
        {
        case GAME_STATE_GAMEPLAY:
            // Game main loop processing goes here
            // Scroll background here to avoid screen tearing
            move_bkg(scrollX, 0);

            // Handle player input
            currentObject = &hero;
            currentJoypad = &joypadCurrent;
            currentPreviousJoypad = &joypadPrevious;
            currentPreviousState = &previousState1;

            currentObject->handleInput();
            currentObject->update();
            if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
            {
                updateHitbox();
            }

            currentObject->draw();

            drawHitbox();

            // Switch over to CPU handling
            currentObject = &enemy;
            currentJoypad = &joypadCurrent2;
            currentPreviousJoypad = &joypadPrevious2;
            currentPreviousState = &previousState2;

            currentObject->handleInput();
            currentObject->update();
            currentObject->draw();

            break;

        default:
            break;
        }

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
