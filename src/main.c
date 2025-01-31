#include <gb/gb.h>
#include <stdint.h>
#include "graphics.h"
#include "collision.h"
#include "hero.h"
#include "input.h"
#include "vars.h"

void main(void)
{
    initGfxMainMenu();
    hero.x = 20;
    hero.y = 10;
    hero.speedX = 0;
    hero.speedY = 0;
    hero.state = 0;
    hero.direction = 0;

    // Loop forever
    while (1)
    {

        // Game main loop processing goes here
        handleInputsGameplay();

        //getCollisions();

        updateHero();

        drawHero();

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
