#include <gbdk/platform.h>
#include <stdint.h>
#include "graphics.h"
#include "collision.h"
#include "hero.h"
#include "boss_debug.h"
#include "input.h"
#include "vars.h"

void main(void)
{
#if defined(SEGA)
    __WRITE_VDP_REG(VDP_R2, R2_MAP_0x3800);
    __WRITE_VDP_REG(VDP_R5, R5_SAT_0x3F00);
#endif

    initGfxMainMenu();

    initHero();
    initBossDbg();
    game.selectedSpecials = HERO_ATTACK_UPPERCUT;

    // Loop forever
    while (1)
    {
        // Game main loop processing goes here
        // Handle player input
        currentObject = &hero;
        currentJoypad = &joypadCurrent;
        currentPreviousJoypad = &joypadPrevious;

        currentObject->handleInput();
        currentObject->update();
        if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
        {
            updateHitbox();
        }

        move_bkg(scrollX, 0);

        currentObject->draw();

        drawHitbox();

        // Switch over to CPU handling
        currentObject = &enemy;
        currentJoypad = &joypadCurrent2;
        currentPreviousJoypad = &joypadPrevious2;

        currentObject->handleInput();
        currentObject->update();
        currentObject->draw();

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
