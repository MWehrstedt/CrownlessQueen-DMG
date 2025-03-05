#include <gbdk/platform.h>
#include "animations.h"
#include "hero.h"
#include "collision.h"
#include "moves.h"
#include "strategies.h"
#include "vars.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#pragma bank 255

void updateHeroDrawFrames(void)
{
    if (currentObject->state & HERO_STATE_HURT)
    {
        currentObject->drawFrames = heroHurtFrames;
    }
    else if (currentObject->state & HERO_STATE_JUMPING)
    {
        currentObject->drawFrames = heroJumpingFrames;
    }
    else if (currentObject->state & HERO_STATE_GROUNDED)
    {
        currentObject->drawFrames = heroIdleFrames;
    }
}

/// @brief Draw and animate hero sprite
void drawHero(void) NONBANKED
{
    // NOTE: current offset table breaks GG, maybe fixes itself when implementing flipped sprites
    if (currentObject->direction == HERO_DIRECTION_RIGHT)
    {
        for (iterator = 0; iterator < 9; ++iterator)
        {
            set_sprite_tile(OAM_HERO_SPRITEID + iterator, currentObject->drawFrames[0][iterator] + currentObject->drawIndex);
            set_sprite_prop(OAM_HERO_SPRITEID + iterator, S_FLIPX);
            move_sprite(OAM_HERO_SPRITEID + iterator,
                        currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + currentObject->drawFrames[2][iterator],
                        currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + currentObject->drawFrames[3][iterator]);
        }
    }
    else
    {
        for (iterator = 0; iterator < 9; ++iterator)
        {
            set_sprite_tile(OAM_HERO_SPRITEID + iterator, currentObject->drawFrames[0][iterator] + currentObject->drawIndex);
            set_sprite_prop(OAM_HERO_SPRITEID + iterator, 0);
            move_sprite(OAM_HERO_SPRITEID + iterator,
                        currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + currentObject->drawFrames[1][iterator],
                        currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + currentObject->drawFrames[3][iterator]);
        }
    }
}
// BANKREF(drawHero)

void initHero(void) NONBANKED
{
    hero.human = true;
    hero.draw = &drawHero;
    hero.handleInput = &heroInputs;
    hero.update = &updateHero;
    hero.x = 20;
    hero.y = 10;
    hero.speedX = 0;
    hero.speedY = 0;
    hero.state = 0;
    hero.direction = 0;
    hero.drawIndex = 0;

    hero.strategyIndex = 0;
    hero.strategy = dummyStrategy;
    hero.drawFrames = heroJumpingFrames;
    hero.currentAttack = HERO_CURRENT_ATTACK_NONE;

    heroAttackHitbox.counter = 0;
    heroAttackHitbox.attribute = 0;
}
// BANKREF(initHero)

/// @brief Main hero routine
void updateHero(void) NONBANKED
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

    // Check collision with enemy
    if (!(currentObject->state & HERO_STATE_HURT) && currentObject->invulnerability == 0 && checkCollisionObject())
    {
        currentObject->state |= HERO_STATE_HURT;
        currentObject->stateCounter = HERO_TIMER_HURT;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
            currentObject->speedX = HERO_KNOCKBACK_HORIZONTAL;
        else
            currentObject->speedX = -HERO_KNOCKBACK_HORIZONTAL;

        currentObject->speedY = HERO_KNOCKBACK_VERTICAL;
    }

    /*  ----------------
            Speed and Scrolling
        ----------------*/
    // Apply new speed
    currentObject->x += currentObject->speedX;
    currentObject->y += currentObject->speedY;

    // Update draw coordinates
    if (currentObject->x < DEVICE_SCREEN_PX_WIDTH / 2)
    {
        currentObject->drawX = currentObject->x;
        scrollX = 0;
        // move_bkg(0, 0);
    }
    else if (currentObject->x > 255 - (DEVICE_SCREEN_PX_WIDTH / 2))
    {
        currentObject->drawX = currentObject->x - 95;
        scrollX = 95;
        // move_bkg(95, 0);
    }
    else
    {
        currentObject->drawX = (DEVICE_SCREEN_PX_WIDTH / 2);
        scrollX = currentObject->x - 80;
        // move_bkg(currentObject->x - 80, 0);
    }

    currentObject->drawY = currentObject->y;

    // Apply friction for next frame
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

    // Clear grounded flag if still in the air
    if (currentObject->speedY != 0)
    {
        currentObject->state &= ~HERO_STATE_GROUNDED;
    }

    /*  ----------------
            Counters
        ----------------*/
    // Update attack counter if needed
    if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
    {
        if ((--heroAttackHitbox.counter) == 0)
        {
            currentObject->state &= ~HERO_STATE_ATTACKING;
            heroAttackHitbox.attribute &= ~HITBOX_ACTIVE;
        }
    }

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
    }

    // Update animation frame offset
    // TODO: insert logic to check animation length and update frequency

    /*  ----------------
            CPU Input
        ----------------*/
    if (!currentObject->human && ++currentObject->buttonIndex == 40)
    {
        currentObject->buttonIndex = 0;
    }

    /*  ----------------
            State handling
        ----------------*/
    if (*currentPreviousState != currentObject->state)
    {
        updateHeroDrawFrames();
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

            // if grounded, apply smaller vertical speed
            if (!(hero.state & HERO_STATE_GROUNDED))
            {
                hero.speedY = HERO_UPPERCUT_JUMP_SPEED;
            }
            else
            {
                hero.speedY = HERO_UPPERCUT_SPEED;
            }
            hero.currentAttack = 1;
        }
        else
        {
            hero.currentAttack = 0;
        }

        break;
    }

    // Set move metadata and activate hitbox
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
    // Save previous inputs
    *currentPreviousState = currentObject->state;

    if (currentObject->human)
    {
        *currentJoypad = joypad();
    }
    else
    {
        *currentJoypad = currentObject->strategy[currentObject->strategyIndex][currentObject->buttonIndex];
    }

    // If not attacking
    if (!(currentObject->state & HERO_STATE_ATTACKING) && !(currentObject->state & HERO_STATE_HURT))
    {
        // Movement
        if (*currentJoypad & J_LEFT)
        {
            currentObject->speedX = -HERO_WALK_SPEED;
            currentObject->direction = HERO_DIRECTION_LEFT;
        }
        else if (*currentJoypad & J_RIGHT)
        {
            currentObject->speedX = HERO_WALK_SPEED;
            currentObject->direction = HERO_DIRECTION_RIGHT;
        }

        // Jump
        if (currentObject->state & HERO_STATE_GROUNDED && (*currentJoypad & J_A) && !(*currentPreviousJoypad & J_A))
        {
            currentObject->speedY = HERO_JUMP_SPEED;
            currentObject->state |= HERO_STATE_JUMPING;
        }

        // Charging
        if (*currentJoypad & J_UP)
        {
            currentObject->state |= HERO_STATE_CHARGING;
        }
        else
        {
            currentObject->state &= ~HERO_STATE_CHARGING;
        }

        // Attack
        if ((*currentJoypad & J_B) && !(*currentPreviousJoypad & J_B))
        {
            currentObject->state |= HERO_STATE_ATTACKING;
            setupMove();
        }
    }

    *currentPreviousJoypad = *currentJoypad;
}
