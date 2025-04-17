#include <gbdk/platform.h>
#include "bossDbgAnimations.h"
#include "audio.h"
#include "boss_debug.h"
#include "collision.h"
#include "graphics.h"
#include "moves.h"
#include "strategies.h"
#include "vars.h"

#pragma bank 255

void updateBossDbgDrawFrames(void)
{
    if (currentObject->state & HERO_STATE_HURT)
    {
        currentObject->drawFrames = bossDbgHurtFrames;
        // update HUD
        updateHealthBar();
    }
    else
    {
        currentObject->drawFrames = bossDbgIdleFrames;
    }
}

/// @brief Draw and animate boss sprite
void drawBossDbg(void) NONBANKED
{
    for (iterator = 0; iterator < 9; ++iterator)
    {
        set_sprite_tile(OAM_ENEMY_SPRITEID + iterator, currentObject->drawFrames[0][(currentObject->drawIndex * 9) + iterator]);

        temp = currentObject->drawFrames[2][iterator];
        temp = currentObject->drawFrames[3][iterator];

        // Set sprite attributes
        move_sprite(OAM_ENEMY_SPRITEID + iterator,
                    currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + currentObject->drawFrames[2][iterator],
                    currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + currentObject->drawFrames[3][iterator]);
    }
}

BANKREF(drawBossDbg)

/// @brief Initialize boss
void initBossDbg(void) NONBANKED
{
    enemy.human = false;
    enemy.draw = &drawBossDbg;
    enemy.handleInput = &heroInputs;
    enemy.update = &updateBossDbg;

    enemy.health = 32;
    enemy.maxHealth = 32;
    enemy.x = 104;
    enemy.y = 48;
    enemy.speedX = 0;
    enemy.speedY = 0;
    enemy.state = 0;
    enemy.direction = 0;
    enemy.buttonIndex = 0;
    enemy.strategyIndex = 0;
    hero.drawIndex = 0;

    enemy.strategy = dummyStrategy;
    // enemy.strategy = bossDbgStrategies;
    enemy.drawFrames = bossDbgIdleFrames;

    // Init HUD
    updateHealthBar();
}
BANKREF(initBossDbg)

/// @brief Handles boss inputs
void bossDbgInputs(void) NONBANKED
{
    // *currentPreviousState = currentObject->state;

    // if (currentObject->human)
    // {
    //     *currentJoypad = joypad();
    // }
    // else
    // {
    //     *currentJoypad = currentObject->strategy[currentObject->strategyIndex][currentObject->buttonIndex];
    // }

    // // Jump
    // if (currentObject->state & HERO_STATE_GROUNDED && (*currentJoypad & J_A) && !(*currentPreviousJoypad & J_A))
    // {
    //     currentObject->speedY = HERO_JUMP_SPEED;
    //     currentObject->state |= HERO_STATE_JUMPING;
    // }

    // // Movement
    // if (*currentJoypad & J_RIGHT)
    // {
    //     currentObject->speedX = HERO_WALK_SPEED;
    //     currentObject->direction = HERO_DIRECTION_RIGHT;
    // }
    // else if (*currentJoypad & J_LEFT)
    // {
    //     currentObject->speedX = -HERO_WALK_SPEED;
    //     currentObject->direction = HERO_DIRECTION_LEFT;
    // }

    // *currentPreviousJoypad = *currentJoypad;
}
BANKREF(bossDbgInputs)

/// @brief Main boss routine
void updateBossDbg(void) NONBANKED
{
    /*  ----------------
            Gravity
        ----------------*/
    // Apply gravity
    if (currentObject->speedY < GAME_GRAVITY_MAX)
    {
        currentObject->speedY += GAME_GRAVITY_STEP;
    }

    /*  ----------------
            Collision
        ----------------*/
    checkCollisionBackgroundX();
    checkCollisionBackgroundY();

    // Check horizontal collision
    if (targetTileHorizontal.centerValue == 1)
    {
        if (currentObject->speedX > 0)
        {
            currentObject->speedX = -(currentObject->x + currentObject->speedX + HITBOX_SIZE_X) % HITBOX_TILESIZE + 2;
        }
        else if (currentObject->speedX < 0)
        {
            currentObject->speedX = HITBOX_TILESIZE - ((currentObject->x + currentObject->speedX + HITBOX_OFFSET_LEFT) % HITBOX_TILESIZE) - 2;
        }
    }

    // Check vertical collision
    if (targetTileVertical.centerValue == 1)
    {
        if (currentObject->speedY > 0)
        {
            currentObject->speedY -= ((currentObject->y + currentObject->speedY + HITBOX_SIZE_Y) % HITBOX_TILESIZE) - 1;

            // Set grounded flag
            currentObject->state |= HERO_STATE_GROUNDED;
            currentObject->state &= ~HERO_STATE_JUMPING;
        }
        else if (currentObject->speedY < 0)
        {
            currentObject->speedY = HITBOX_TILESIZE - ((currentObject->y + currentObject->speedY) % HITBOX_TILESIZE) - 1;
        }
    }

    // Check collision with player attack hitbox
    if ((heroAttackHitbox.attribute & HITBOX_ACTIVE) && !(currentObject->state & HERO_STATE_HURT) && currentObject->invulnerability == 0 && checkCollisionHitbox())
    {
        currentObject->state |= HERO_STATE_HURT;
        currentObject->stateCounter = HERO_TIMER_HURT;
        currentObject->health -= heroAttackHitbox.damage;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
            currentObject->speedX = HERO_KNOCKBACK_HORIZONTAL;
        else
            currentObject->speedX = -HERO_KNOCKBACK_HORIZONTAL;

        currentObject->speedY = HERO_KNOCKBACK_VERTICAL;

        playSFX(4);
    }

    /*  ----------------
            Apply Speed
        ----------------*/
    currentObject->x += currentObject->speedX;
    currentObject->y += currentObject->speedY;

    currentObject->drawX = currentObject->x; // - scrollX;
    currentObject->drawY = currentObject->y;

    if (currentObject->state & HERO_STATE_GROUNDED && currentObject->speedX > 0)
    {
        currentObject->speedX -= GAME_FRICTION;
    }
    else if (currentObject->state & HERO_STATE_GROUNDED && currentObject->speedX < 0)
    {
        currentObject->speedX += GAME_FRICTION;
    }

    /*  ----------------
            Flags
        ----------------*/

    // Check if hero is hurt and count down
    if (currentObject->state & HERO_STATE_HURT && !(--currentObject->stateCounter))
    {
        currentObject->invulnerability = HERO_TIMER_INVULNERABILITY;
        currentObject->state &= ~HERO_STATE_HURT;
    }

    // Count down invulnerability
    if (currentObject->invulnerability)
    {
        --currentObject->invulnerability;

        // Adjust drawing position during Iframes
        if (!(currentObject->invulnerability & 0x3))
        {
            currentObject->drawX = 160;
            currentObject->drawY = 150;
        }
    }

    // Face player
    if (currentObject->x + 8 < hero.x)
    {
        currentObject->direction = HERO_DIRECTION_RIGHT;
    }
    else
    {
        currentObject->direction = HERO_DIRECTION_LEFT;
    }

    /*  ----------------
            CPU Input
        ----------------*/
    if (!currentObject->human && ++currentObject->buttonIndex == 5)
    {
        currentObject->buttonIndex = 0;
    }

    /*  ----------------
            State handling
        ----------------*/
    if (*currentPreviousState != currentObject->state)
    {
        updateBossDbgDrawFrames();
    }
    // #if defined(GAMEGEAR)
    //     // On Game Gear, load flipped sprite set due to no sprite flipping
    //     if (previousDirection2 != currentObject->direction)
    //     {
    //         loadPlayer2Sprites();
    //     }
    // #endif
}
BANKREF(updateBossDbg)