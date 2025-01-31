#include <gb/gb.h>
#include <gbdk/platform.h>
#include "hero.h"
#include "collision.h"
#include "vars.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#pragma bank 255

/// @brief Draw and animate hero sprite
void drawHero(void) BANKED
{
    move_sprite(0, hero.drawX + 8, hero.drawY + 16);
    move_sprite(1, hero.drawX + 16, hero.drawY + 16);
    move_sprite(2, hero.drawX + 8, hero.drawY + 24);
    move_sprite(3, hero.drawX + 16, hero.drawY + 24);
    move_sprite(4, hero.drawX + 8, hero.drawY + 32);
    move_sprite(5, hero.drawX + 16, hero.drawY + 32);
}
BANKREF(drawHero)

/// @brief Main hero routine
void updateHero(void) BANKED
{

    // Apply gravity
    if (hero.speedY < GAME_GRAVITY_MAX)
    {
        hero.speedY += GAME_GRAVITY_STEP;
    }

    checkCollisionBackgroundX();
    checkCollisionBackgroundY();

    // Check background collisions
    // Check horizontal collision
    if (targetTileHorizontal.centerValue == 1)
    {
        if (hero.speedX > 0)
        {
            hero.speedX = -(hero.x + hero.speedX + HITBOX_SIZE_X) % HITBOX_TILESIZE;
        }
        else if (hero.speedX < 0)
        {
            hero.speedX = HITBOX_TILESIZE - ((hero.x + hero.speedX + HITBOX_OFFSET_LEFT) % HITBOX_TILESIZE) - 1;
        }
    }

    // Check horizontal collision
    if (targetTileVertical.centerValue == 1)
    {
        if (hero.speedY > 0)
        {
            hero.speedY -= ((hero.y + hero.speedY + HITBOX_SIZE_Y) % HITBOX_TILESIZE) + 1;

            // Set grounded flag and clear jumping flag
            hero.state |= HERO_STATE_GROUNDED;
            hero.state &= ~HERO_STATE_JUMPING;
        }
        else if (hero.speedY < 0)
        {
            hero.speedY = HITBOX_TILESIZE - ((hero.y + hero.speedY) % HITBOX_TILESIZE) - 1;
        }
    }

    hero.x += hero.speedX;
    hero.y += hero.speedY;

    // Update draw coordinates
    if (hero.x < DEVICE_SCREEN_PX_WIDTH / 2)
    {
        hero.drawX = hero.x;
        move_bkg(0, 0);
    }
    else if (hero.x > 255 - (DEVICE_SCREEN_PX_WIDTH / 2))
    {
        hero.drawX = hero.x - 95;
        move_bkg(95, 0);
    }
    else
    {
        hero.drawX = (DEVICE_SCREEN_PX_WIDTH / 2);
        move_bkg(hero.x - 80, 0);
    }

    hero.drawY = hero.y;

    // Clear grounded flag if still in the air
    if (hero.speedY != 0)
    {
        hero.state &= ~HERO_STATE_GROUNDED;
    }

    if (hero.speedX > 0)
    {
        hero.speedX -= GAME_FRICTION;
    }
    else if (hero.speedX < 0)
    {
        hero.speedX += GAME_FRICTION;
    }
}
BANKREF(updateHero)

/// @brief Handle knockback during hitstate
void handleHitstate(void) BANKED
{
}
BANKREF(handleHitstate)

/// @brief Main weapon routine
void updateWeapon(void) BANKED
{
}
BANKREF(updateWeapon)
