#include <gbdk/platform.h>
#include <stdint.h>
#include "graphics.h"
#include "collision.h"
#include "hero.h"
#include "boss_debug.h"
#include "input.h"
#include "vars.h"
#if defined(GAMEBOY)
#include "../src/gb/sgb.h"
#include "../res/gb/sgb_border.h"
#endif

void initTraining(void)
{
    currentObject = &hero;
    initHero();
    currentObject = &enemy;
    initBossDbg();

    game.state = GAME_STATE_GAMEPLAY;
}

void main(void)
{
#if defined(GAMEGEAR)
    __WRITE_VDP_REG(VDP_R2, R2_MAP_0x3800);
    __WRITE_VDP_REG(VDP_R5, R5_SAT_0x3F00);
#elif defined(GAMEBOY)

    // Wait 4 frames
    // For SGB on PAL SNES this delay is required on startup, otherwise borders don't show up
    for (iterator = 4; iterator != 0; iterator--)
        vsync();

    // The display must be ON before calling set_sgb_border()

    if (sgb_check())
    {
        DISPLAY_ON;
        set_sgb_border(sgb_border_tiles,
                       sizeof(sgb_border_tiles),
                       sgb_border_map,
                       sizeof(sgb_border_map),
                       sgb_border_palettes, sizeof(sgb_border_palettes));
    }
#endif

    initGfxMainMenu();

    game.state = GAME_STATE_INITGAMEPLAY;
    // game.selectedSpecials = HERO_ATTACK_UPPERCUT;

    // Loop forever
    while (1)
    {
        switch (game.state)
        {
        case GAME_STATE_INITGAMEPLAY:
            initTraining();
            break;
        case GAME_STATE_GAMEPLAY:
            // Game main loop processing goes here
            // Scroll background here to avoid screen tearing
            // move_bkg(scrollX, 0);

            // Handle player input
            currentObject = &hero;
            currentJoypad = &joypadCurrent;
            currentPreviousJoypad = &joypadPrevious;
            currentPreviousState = &previousState1;
            previousDirection1 = hero.direction;

            currentObject->handleInput();
            currentObject->update();

            if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
            {
                updateHitbox();
            }

            currentObject->draw();
            drawHitbox();

#if defined(GAMEGEAR)
            // On Game Gear, load flipped sprite set due to no sprite flipping
            if (previousDirection1 != currentObject->direction)
            {
                wait_vbl_done();
                loadPlayer1Sprites();
            }
#endif

            // Switch over to CPU handling
            currentObject = &enemy;
            currentJoypad = &joypadCurrent2;
            currentPreviousJoypad = &joypadPrevious2;
            currentPreviousState = &previousState2;
            previousDirection2 = enemy.direction;

            currentObject->handleInput();
            currentObject->update();
            currentObject->draw();

#if defined(GAMEGEAR)
            // On Game Gear, load flipped sprite set due to no sprite flipping
            if (previousDirection2 != currentObject->direction)
            {
                wait_vbl_done();
                loadPlayer2Sprites();
            }
#endif

            break;

        default:
            break;
        }

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
