#include <gbdk/platform.h>
#include <stdint.h>
#include "graphics.h"
#include "collision.h"
#include "hero.h"
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
    game.selectedSpecials = HERO_ATTACK_UPPERCUT;

    // Loop forever
    while (1)
    {
        // Game main loop processing goes here
        // handleInputsGameplay();
        // updateHero();

        hero.handleInput();
        hero.update();
        if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
        {
            updateHitbox();
        }

        // drawHero();
        hero.draw();
        drawHitbox();

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
