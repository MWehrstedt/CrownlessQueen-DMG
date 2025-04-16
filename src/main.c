#include <gbdk/platform.h>
#include <stdint.h>
#include "audio.h"
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
    DISPLAY_OFF;
    initGfxTraining();

    currentObject = &hero;
    initHero();
    currentObject = &enemy;
    initBossDbg();

    unmuteAudio();
    game.state = GAME_STATE_GAMEPLAY;
}

void initMainMenu(void)
{
    DISPLAY_OFF;
    initGfxMainMenu();
    muteAudio();
    game.state = GAME_STATE_MAINMENU;
    
}

void pausing(void)
{
    HIDE_SPRITES;
    // TODO: transition smoothly
    move_win(7, 80);

    muteAudio();
    game.state = GAME_STATE_PAUSED;
}

void unpausing(void)
{
    SHOW_SPRITES;
    // TODO: transition smoothly
    move_win(7, 112);

    unmuteAudio();
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
        // CBTFX_SGB = 0xff;
    }

    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
#endif

    initSong();

    game.state = GAME_STATE_INTRO;
    game.selectedMenuItem = 0;

    // Loop forever
    while (1)
    {
        switch (game.state)
        {
        case GAME_STATE_INTRO:
            initMainMenu();
            break;
        case GAME_STATE_MAINMENU:
            mainmenuInputs();
            break;
        case GAME_STATE_INITGAMEPLAY:
            initTraining();
            break;
        case GAME_STATE_PAUSING:
            pausing();
            break;
        case GAME_STATE_UNPAUSING:
            unpausing();
            break;
        case GAME_STATE_PAUSED:
            pauseInputs();
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
                vsync();
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
                vsync();
                loadPlayer2Sprites();
            }
#endif

            break;

        default:
            break;
        }

        playSong();

        // Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
