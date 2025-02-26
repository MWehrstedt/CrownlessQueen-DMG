#include <gbdk/platform.h>
#include "boss_debug.h"
#include "collision.h"
#include "moves.h"
#include "strategies.h"
#include "vars.h"

#pragma bank 255

/// @brief Draw and animate boss sprite
void drawBossDbg(void) NONBANKED
{
    move_sprite(20, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(21, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(22, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(23, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(24, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(25, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(26, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
    move_sprite(27, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
    move_sprite(28, currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
}
BANKREF(drawBossDbg)

/// @brief Initialize boss
void initBossDbg(void) NONBANKED
{
    enemy.human = false;
    enemy.draw = &drawBossDbg;
    enemy.handleInput = &bossDbgInputs;
    enemy.update = &updateBossDbg;

    enemy.x = 120;
    enemy.y = 48;
    enemy.speedX = 0;
    enemy.speedY = 0;
    enemy.state = 0;
    enemy.direction = 0;
    enemy.buttonIndex = 0;
    enemy.strategyIndex = 0;
}
BANKREF(initBossDbg)

/// @brief Handles boss inputs
void bossDbgInputs(void) NONBANKED
{
    if (currentObject->human)
    {
        *currentJoypad = joypad();
    }
    else
    {
        *currentJoypad = bossDbgStrategies[currentObject->strategyIndex][currentObject->buttonIndex];
    }


    // Jump
    if (currentObject->state & HERO_STATE_GROUNDED && (*currentJoypad & J_A) && !(*currentPreviousJoypad & J_A))
    {
        currentObject->speedY = HERO_JUMP_SPEED;
        currentObject->state |= HERO_STATE_JUMPING;
    }

    // Movement
    if (*currentJoypad & J_RIGHT)
    {
        currentObject->speedX = HERO_WALK_SPEED;
        currentObject->direction = HERO_DIRECTION_RIGHT;
    } else if (*currentJoypad & J_LEFT)
    {
        currentObject->speedX = -HERO_WALK_SPEED;
        currentObject->direction = HERO_DIRECTION_LEFT;
    }

    *currentPreviousJoypad = *currentJoypad;
}
BANKREF(bossDbgInputs)

/// @brief Main boss routine
void updateBossDbg(void) NONBANKED
{

    // Apply gravity
    if (currentObject->speedY < GAME_GRAVITY_MAX)
    {
        currentObject->speedY += GAME_GRAVITY_STEP;
    }

    checkCollisionBackgroundX();
    checkCollisionBackgroundY();

    // Check background collisions
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

    // Check horizontal collision
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

    currentObject->x += currentObject->speedX;
    currentObject->y += currentObject->speedY;

    currentObject->drawX = currentObject->x - scrollX;
    currentObject->drawY = currentObject->y;

    if (currentObject->state & HERO_STATE_GROUNDED && currentObject->speedX > 0)
    {
        currentObject->speedX -= GAME_FRICTION;
    }
    else if (currentObject->state & HERO_STATE_GROUNDED && currentObject->speedX < 0)
    {
        currentObject->speedX += GAME_FRICTION;
    }

    // Update button index if CPU
    if (!currentObject->human && ++currentObject->buttonIndex == 40)
    {
        currentObject->buttonIndex = 0;
    }
}
BANKREF(updateBossDbg)