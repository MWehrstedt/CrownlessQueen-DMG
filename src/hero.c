//#include <gb/gb.h>
#include <gbdk/platform.h>
#include "hero.h"
#include "collision.h"
#include "moves.h"
#include "vars.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#pragma bank 255

/// @brief Draw and animate hero sprite
void drawHero(void) NONBANKED
{
    move_sprite(0, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(1, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(2, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    move_sprite(3, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(4, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(5, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 8);
    move_sprite(6, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
    move_sprite(7, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 8, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
    move_sprite(8, hero.drawX + DEVICE_SPRITE_PX_OFFSET_X + 16, hero.drawY + DEVICE_SPRITE_PX_OFFSET_Y + 16);
}
//BANKREF(drawHero)

void initHero(void) NONBANKED
{
    hero.draw = &drawHero;
    hero.handleInput = &heroInputs;
    hero.update = &updateHero;
    hero.x = 20;
    hero.y = 10;
    hero.speedX = 0;
    hero.speedY = 0;
    hero.state = 0;
    hero.direction = 0;

    heroAttackHitbox.counter = 0;
    heroAttackHitbox.attribute = 0;
}
//BANKREF(initHero)

/// @brief Main hero routine
void updateHero(void) NONBANKED
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
            hero.speedX = -(hero.x + hero.speedX + HITBOX_SIZE_X) % HITBOX_TILESIZE + 2;
        }
        else if (hero.speedX < 0)
        {
            hero.speedX = HITBOX_TILESIZE - ((hero.x + hero.speedX + HITBOX_OFFSET_LEFT) % HITBOX_TILESIZE) - 2;
        }
    }

    // Check horizontal collision
    if (targetTileVertical.centerValue == 1)
    {
        if (hero.speedY > 0)
        {
            hero.speedY -= ((hero.y + hero.speedY + HITBOX_SIZE_Y) % HITBOX_TILESIZE) - 1;

            // Set grounded flag
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

    if (hero.state & HERO_STATE_GROUNDED && hero.speedX > 0)
    {
        hero.speedX -= GAME_FRICTION;
    }
    else if (hero.state & HERO_STATE_GROUNDED && hero.speedX < 0)
    {
        hero.speedX += GAME_FRICTION;
    }

    // Clear grounded flag if still in the air
    if (hero.speedY != 0)
    {
        hero.state &= ~HERO_STATE_GROUNDED;
    }

    // Update attack counter if needed
    if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
    {
        if ((--heroAttackHitbox.counter) == 0)
        {
            hero.state &= ~HERO_STATE_ATTACKING;
            heroAttackHitbox.attribute &= ~HITBOX_ACTIVE;
        }
    }
}
// BANKREF(updateHero)

void updateHitbox(void) BANKED
{
    if (heroAttackHitbox.counter >= heroMoveFrames[hero.currentAttack].startup || heroAttackHitbox.counter <= heroMoveFrames[hero.currentAttack].recovery)
    {
        heroAttackHitbox.x = 200;
        heroAttackHitbox.y = 200;
        heroAttackHitbox.drawX = 200;
        heroAttackHitbox.drawY = 200;
    }
    else
    {
        if (hero.direction & HERO_DIRECTION_LEFT)
        {
            heroAttackHitbox.x = hero.x - 8;
            heroAttackHitbox.drawX = hero.drawX - 8;
        }
        else
        {
            heroAttackHitbox.x = hero.x + HITBOX_SIZE_X + 8;
            heroAttackHitbox.drawX = hero.drawX + HITBOX_SIZE_X + 8;
        }

        heroAttackHitbox.y = hero.y + 10;
        heroAttackHitbox.drawY = hero.drawY + 10;
    }
}
BANKREF(updateHitbox)

void drawHitbox(void) BANKED
{
    if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
    {
        move_sprite(12, heroAttackHitbox.drawX + DEVICE_SPRITE_PX_OFFSET_X, heroAttackHitbox.drawY + DEVICE_SPRITE_PX_OFFSET_Y - 8);
        move_sprite(13, heroAttackHitbox.drawX + DEVICE_SPRITE_PX_OFFSET_X, heroAttackHitbox.drawY + DEVICE_SPRITE_PX_OFFSET_Y);
    }
    else
    {
        move_sprite(12, 220, 220);
        move_sprite(13, 220, 220);
    }
}
BANKREF(drawHitbox)

void setupMove(void) BANKED
{
    switch (game.selectedSpecials)
    {
    case HERO_ATTACK_UPPERCUT:
        if (hero.state & HERO_STATE_CHARGING)
        {
            // check for jumping variant, add vertical boost to it
            if (!(hero.state & HERO_STATE_GROUNDED))
            {
                hero.speedY = HERO_UPPERCUT_JUMP_SPEED;
            }
            hero.currentAttack = 1;
        }
        else
        {
            hero.currentAttack = 0;
        }

        break;
    }

    heroAttackHitbox.counter = heroMoveFrames[hero.currentAttack].length;
    heroAttackHitbox.damage = heroMoveFrames[hero.currentAttack].damage;
    heroAttackHitbox.attribute |= HITBOX_ACTIVE;
}
BANKREF(setupMove)

/// @brief Main weapon routine
void updateWeapon(void) BANKED
{
}
BANKREF(updateWeapon)

/// @brief Handles inputs on main menu screen
void heroInputs(void) NONBANKED
{
    joypadCurrent = joypad();

    // If not attacking
    if (!(hero.state & HERO_STATE_ATTACKING))
    {
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

        // Charging
        if (joypadCurrent & J_UP)
        {
            hero.state |= HERO_STATE_CHARGING;
        }
        else
        {
            hero.state &= ~HERO_STATE_CHARGING;
        }

        // Attack
        if ((joypadCurrent & J_B) && !(joypadPrevious & J_B))
        {
            hero.state |= HERO_STATE_ATTACKING;
            setupMove();
        }
    }

    joypadPrevious = joypadCurrent;
}
