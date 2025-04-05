#include <gbdk/platform.h>
#include "heroAnimations.h"
#include "graphics.h"
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

    currentObject->animationCounter = 0;
    currentObject->drawIndex = 0;

    if (currentObject->state & HERO_STATE_HURT)
    {
        currentObject->animationPlay = false;
        currentObject->drawFrames = heroHurtFrames;

        // update HUD
        updateHealthBar();
    }
    else if (currentObject->state & HERO_STATE_ATTACKING)
    {
        currentObject->animationPlay = false;

        if (currentObject->currentAttack == HERO_ATTACK_UPPERCUT)
        {
            currentObject->drawFrames = heroUppercutFrames;
        }
        else if (currentObject->state & HERO_STATE_JUMPING)
        {
            currentObject->drawFrames = heroJumpingAttackFrames;
        }
        else
        {
            currentObject->drawFrames = heroAttackFrames;
        }
    }
    else if (currentObject->state & HERO_STATE_JUMPING)
    {
        currentObject->animationPlay = false;
        currentObject->drawFrames = heroJumpingFrames;
    }
    else if (currentObject->state & HERO_STATE_WALKING)
    {
        currentObject->animationPlay = true;
        currentObject->drawFrames = heroWalkingFrames;
        currentObject->drawFrameLength = 4;
        currentObject->drawFrameRate = 12;
    }
    else if (currentObject->state & HERO_STATE_GROUNDED)
    {
        currentObject->animationPlay = true;
        currentObject->drawFrames = heroIdleFrames;
        currentObject->drawFrameLength = 2;
        currentObject->drawFrameRate = 16;
    }
}

/// @brief Draw and animate hero sprite
void drawHero(void) NONBANKED
{
    if (currentObject->direction == HERO_DIRECTION_RIGHT)
    {
        for (iterator = 0; iterator < 12; ++iterator)
        {
            set_sprite_tile(OAM_HERO_SPRITEID + iterator, currentObject->drawFrames[0][(currentObject->drawIndex * 12) + iterator]);
            if (HARDWARE_SPRITE_CAN_FLIP_X)
            {
                set_sprite_prop(OAM_HERO_SPRITEID + iterator, 0);
            }
#if defined(GAMEGEAR)
            // Load values into a temporary variable, presumably to correct endianness
            temp = currentObject->drawFrames[2][iterator];
            temp = currentObject->drawFrames[3][iterator];
#endif

            move_sprite(OAM_HERO_SPRITEID + iterator,
                        currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + currentObject->drawFrames[2][iterator],
                        currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + currentObject->drawFrames[3][iterator]);
        }
    }
    else
    {
        for (iterator = 0; iterator < 12; ++iterator)
        {
            set_sprite_tile(OAM_HERO_SPRITEID + iterator, currentObject->drawFrames[0][(currentObject->drawIndex * 12) + iterator]);
            if (HARDWARE_SPRITE_CAN_FLIP_X)
            {
                set_sprite_prop(OAM_HERO_SPRITEID + iterator, S_FLIPX);
            }

#if defined(GAMEGEAR)
            // Load values into a temporary variable, presumably to correct endianness
            temp = currentObject->drawFrames[1][iterator];
            temp = currentObject->drawFrames[3][iterator];
#endif

            move_sprite(OAM_HERO_SPRITEID + iterator,
                        currentObject->drawX + DEVICE_SPRITE_PX_OFFSET_X + currentObject->drawFrames[1][iterator],
                        currentObject->drawY + DEVICE_SPRITE_PX_OFFSET_Y + currentObject->drawFrames[3][iterator]);
        }
    }
}
BANKREF(drawHero)

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
    hero.direction = HERO_DIRECTION_RIGHT;
    hero.drawIndex = 0;
    hero.health = 20;
    hero.maxHealth = 20;
    hero.attackChargeCounter = 0;

    hero.animationCounter = 0;
    hero.drawFrameLength = 4;
    hero.drawFrameRate = 10;
    hero.strategyIndex = 0;
    hero.strategy = dummyStrategy;
    hero.drawFrames = heroJumpingFrames;
    hero.currentAttack = HERO_CURRENT_ATTACK_NONE;

    heroAttackHitbox.counter = 0;
    heroAttackHitbox.attribute = 0;

    // Init HUD
    updateHealthBar();
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
        currentObject->health--;

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

    // // Update draw coordinates
    // if (currentObject->x < DEVICE_SCREEN_PX_WIDTH / 2)
    // {
    //     currentObject->drawX = currentObject->x;
    //     scrollX = 0;
    //     // move_bkg(0, 0);
    // }
    // else if (currentObject->x > 255 - (DEVICE_SCREEN_PX_WIDTH / 2))
    // {
    //     currentObject->drawX = currentObject->x - 95;
    //     scrollX = 95;
    //     // move_bkg(95, 0);
    // }
    // else
    // {
    //     currentObject->drawX = (DEVICE_SCREEN_PX_WIDTH / 2);
    //     scrollX = currentObject->x - 80;
    //     // move_bkg(currentObject->x - 80, 0);
    // }

    currentObject->drawX = currentObject->x;
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

    // // Clear uppercut flag
    // if (currentObject->speedY == 0 && currentObject->state & HERO_STATE_ATTACKING && currentObject->currentAttack == HERO_ATTACK_UPPERCUT
    // && heroAttackHitbox.counter < 25)
    // {
    //     heroAttackHitbox.counter = 5;
    // }

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

    if (currentObject->animationPlay && ++currentObject->animationCounter == currentObject->drawFrameRate)
    {
        currentObject->animationCounter = 0;
        currentObject->drawIndex = (currentObject->drawIndex + 1) % currentObject->drawFrameLength;
    }

    /*  ----------------
            CPU Input
        ----------------*/
    if (!currentObject->human && ++currentObject->buttonIndex == 20)
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
    // Move hitbox away during startup and recovery
    if (heroAttackHitbox.counter >= heroMoveFrames[currentObject->currentAttack].startup ||
        heroAttackHitbox.counter <= heroMoveFrames[currentObject->currentAttack].recovery)
    {
        heroAttackHitbox.x = 200;
        heroAttackHitbox.y = 200;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
        {
            heroAttackHitbox.drawX = currentObject->drawX + 4;
        }
        else
        {
            heroAttackHitbox.drawX = currentObject->drawX + 15;
        }

        heroAttackHitbox.drawY = currentObject->drawY + 16;
    }
    // Move hitbox away during dash
    else if (currentObject->currentAttack == 3)
    {
        heroAttackHitbox.x = 200;
        heroAttackHitbox.y = 200;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
        {
            heroAttackHitbox.drawX = currentObject->drawX - 4;
        }
        else
        {
            heroAttackHitbox.drawX = currentObject->drawX + 20;
        }

        heroAttackHitbox.drawY = currentObject->drawY + 15;
    }
    else
    // Active
    {
        if (currentObject->direction & HERO_DIRECTION_LEFT)
        {
            heroAttackHitbox.x = currentObject->x + heroMoveHitboxOffsetXLeft[currentObject->currentAttack];
            heroAttackHitbox.drawX = currentObject->drawX + heroMoveHitboxOffsetXLeft[currentObject->currentAttack];
        }
        else
        {
            heroAttackHitbox.x = currentObject->x + heroMoveHitboxOffsetXRight[currentObject->currentAttack];
            heroAttackHitbox.drawX = currentObject->drawX + heroMoveHitboxOffsetXRight[currentObject->currentAttack];
        }

        heroAttackHitbox.y = currentObject->y + heroMoveHitboxOffsetY[currentObject->currentAttack];
        heroAttackHitbox.drawY = currentObject->drawY + heroMoveHitboxOffsetY[currentObject->currentAttack];
    }

    // Update move specific
    switch (currentObject->currentAttack)
    {
    case HERO_ATTACK_UPPERCUT:
        if (heroAttackHitbox.counter == heroMoveFrames[currentObject->currentAttack].startup)
        {
            if (!(currentObject->state & HERO_STATE_GROUNDED))
            {
                currentObject->speedY = HERO_UPPERCUT_JUMP_SPEED;
            }
            else
            {
                currentObject->speedY = HERO_UPPERCUT_VERTICALSPEED;
            }

            if (currentObject->direction & HERO_DIRECTION_LEFT)
            {
                currentObject->speedX = -HERO_UPPERCUT_HORIZONTALSPEED;
            }
            else
            {
                currentObject->speedX = HERO_UPPERCUT_HORIZONTALSPEED;
            }
        }

        // Move visible hitbox away during uppercut
        heroAttackHitbox.drawX = 200;
        heroAttackHitbox.drawY = 200;

        break;
    case 2:
    case 3:
        currentObject->invulnerability = 2;
        break;
    }
}
BANKREF(updateHitbox)

void drawHitbox(void) BANKED
{
    if (heroAttackHitbox.attribute & HITBOX_ACTIVE)
    {
        move_sprite(12, heroAttackHitbox.drawX + DEVICE_SPRITE_PX_OFFSET_X, heroAttackHitbox.drawY + DEVICE_SPRITE_PX_OFFSET_Y - 8);
    }
    else
    {
        move_sprite(12, 200, 200);
    }
}
BANKREF(drawHitbox)

void setupMove(uint8_t id) BANKED
{
    currentObject->currentAttack = id;

    switch (id)
    {
    case HERO_ATTACK_SIDESTEP:
        if (!(currentObject->state & HERO_STATE_GROUNDED))
            break;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
        {
            currentObject->speedX = -HERO_SIDESTEP_SPEED;
        }
        else
        {
            currentObject->speedX = HERO_SIDESTEP_SPEED;
        }

        currentObject->invulnerability = 1;

        break;
    case HERO_ATTACK_DASH:
        if (!(currentObject->state & HERO_STATE_GROUNDED))
            break;

        if (currentObject->direction & HERO_DIRECTION_LEFT)
        {
            currentObject->speedX = -HERO_DASH_SPEED;
        }
        else
        {
            currentObject->speedX = HERO_DASH_SPEED;
        }

        currentObject->invulnerability = 1;
        break;
    }

    // Set move metadata and activate hitbox
    heroAttackHitbox.counter = heroMoveFrames[currentObject->currentAttack].length;
    heroAttackHitbox.damage = heroMoveFrames[currentObject->currentAttack].damage;
    heroAttackHitbox.width = heroMoveHitboxWidth[currentObject->currentAttack];
    heroAttackHitbox.height = heroMoveHitboxHeight[currentObject->currentAttack];
    heroAttackHitbox.attribute |= HITBOX_ACTIVE;
}
BANKREF(setupMove)

/// @brief Main weapon routine
void updateWeapon(void) BANKED
{
}
BANKREF(updateWeapon)

/// @brief Handles inputs
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
            currentObject->state |= HERO_STATE_WALKING;
        }
        else if (*currentJoypad & J_RIGHT)
        {
            currentObject->speedX = HERO_WALK_SPEED;
            currentObject->direction = HERO_DIRECTION_RIGHT;
            currentObject->state |= HERO_STATE_WALKING;
        }
        else
        {
            currentObject->state &= ~HERO_STATE_WALKING;
        }

        // Jump
        if (currentObject->state & HERO_STATE_GROUNDED && (*currentJoypad & J_A) && !(*currentPreviousJoypad & J_A))
        {
            currentObject->speedY = HERO_JUMP_SPEED;
            currentObject->state |= HERO_STATE_JUMPING;
            currentObject->state &= ~HERO_STATE_WALKING;
        }

        // Charging uppercut
        if (*currentJoypad & J_UP)
        {
            currentObject->state |= HERO_STATE_CHARGING;
        }
        else
        {
            currentObject->state &= ~HERO_STATE_CHARGING;
        }

        // Charging dash
        if (*currentJoypad & J_DOWN)
        {
            currentObject->state |= HERO_STATE_DOWNCHARGING;
        }
        else
        {
            currentObject->state &= ~HERO_STATE_DOWNCHARGING;
        }

        // Attack side step
        if (!(*currentJoypad & J_B) && (*currentPreviousJoypad & J_B) && currentObject->attackChargeCounter == HERO_TIMER_SIDESTEP_MAX)
        {
            currentObject->state |= HERO_STATE_ATTACKING;
            currentObject->attackChargeCounter = 0;
            setupMove(HERO_ATTACK_SIDESTEP);
        }
        else if ((*currentJoypad & J_B) && !(*currentPreviousJoypad & J_B))
        {
            // Attack jab and uppercut
            currentObject->state |= HERO_STATE_ATTACKING;

            if (currentObject->state & HERO_STATE_CHARGING)
            {
                setupMove(HERO_ATTACK_UPPERCUT);
            }
            else if (currentObject->state & HERO_STATE_DOWNCHARGING)
            {
                setupMove(HERO_ATTACK_DASH);
            }
            else
            {
                setupMove(HERO_ATTACK_PUNCH_ONE);
            }
        }

        // Charging Side Step
        if ((*currentJoypad & J_B))
        {
            if (++currentObject->attackChargeCounter > HERO_TIMER_SIDESTEP_MAX)
            {
                currentObject->attackChargeCounter = HERO_TIMER_SIDESTEP_MAX;
                if (currentObject->human)
                    //move_sprite(30, 24 + DEVICE_SPRITE_PX_OFFSET_X, 16 + DEVICE_SPRITE_PX_OFFSET_Y);
                    set_sprite_tile(30, 67);
            }
            else
            {
                if (currentObject->human)
                    //move_sprite(30, 16 + DEVICE_SPRITE_PX_OFFSET_X, 16 + DEVICE_SPRITE_PX_OFFSET_Y);
                    set_sprite_tile(30, 66);
            }
        }
        else
        {
            currentObject->attackChargeCounter = 0;
            if (currentObject->human)
                //move_sprite(30, 10 + DEVICE_SPRITE_PX_OFFSET_X, 16 + DEVICE_SPRITE_PX_OFFSET_Y);
                set_sprite_tile(30, 65);
        }
    }

    *currentPreviousJoypad = *currentJoypad;
}
