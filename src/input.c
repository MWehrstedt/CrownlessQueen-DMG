#include <gb/gb.h>
#include <gbdk/platform.h>
#include "input.h"
#include "vars.h"

#pragma bank 255

/// @brief Handles inputs on main menu screen
void handleInputsGameplay(void) NONBANKED
{
    joypadCurrent = joypad();

    // Movement
    if (joypadCurrent & J_LEFT)
    {
        hero.speedX = -HERO_WALK_SPEED;
        hero.direction = HERO_DIRECTION_LEFT;
    }
    else if (joypadCurrent & J_RIGHT)
    {
        hero.speedX = HERO_WALK_SPEED;
        hero.direction = HERO_DIRECTION_RIGHT;
    }

    // Jump
    if (hero.state & HERO_STATE_GROUNDED && (joypadCurrent & J_A) && !(joypadPrevious & J_A))
    {
        hero.speedY = HERO_JUMP_SPEED;
        hero.state |= HERO_STATE_JUMPING;
    }

    joypadPrevious = joypadCurrent;
}