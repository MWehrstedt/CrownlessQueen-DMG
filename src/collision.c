#include <gbdk/platform.h>
#include <stdint.h>
#include "../include/stdbool.h"
#include "vars.h"
#include "hero.h"
#include "collision.h"
#include "hitmapsPool.h"

#pragma bank 255

BANKREF(getCollisions)
void getCollisions(void) BANKED
{
    checkCollisionBackgroundX();
    checkCollisionBackgroundY();
}

BANKREF(checkCollisionBackgroundX)
void checkCollisionBackgroundX(void) BANKED
{
    if (currentObject->speedX < 0)
    {
        targetTileHorizontal.top = ((currentObject->x + currentObject->speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((currentObject->y + HITBOX_OFFSET_TOP) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.center = ((currentObject->x + currentObject->speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((currentObject->y + 12) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.centerValue = hitmapPool[0][targetTileHorizontal.center];

        targetTileHorizontal.bottom = ((currentObject->x + currentObject->speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((currentObject->y + 24) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
    else
    {
        targetTileHorizontal.top = ((currentObject->x + currentObject->speedX + HITBOX_SIZE_X - HITBOX_OFFSET_RIGHT) / HITBOX_TILESIZE) + (((currentObject->y + HITBOX_OFFSET_TOP) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.center = ((currentObject->x + currentObject->speedX + HITBOX_SIZE_X - HITBOX_OFFSET_RIGHT) / HITBOX_TILESIZE) + (((currentObject->y + 12) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.centerValue = hitmapPool[0][targetTileHorizontal.center];

        targetTileHorizontal.bottom = ((currentObject->x + currentObject->speedX + HITBOX_SIZE_X - HITBOX_OFFSET_RIGHT) / HITBOX_TILESIZE) + (((currentObject->y + 24) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
}

BANKREF(checkCollisionBackgroundY)
void checkCollisionBackgroundY(void) BANKED
{

    // Get tile collisions for hero
    if (currentObject->speedY < 0)
    {
        // Left
        targetTileVertical.top = ((currentObject->x + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY + HITBOX_OFFSET_TOP) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.center = ((currentObject->x + 8) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY + HITBOX_OFFSET_TOP) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.centerValue = hitmapPool[0][targetTileVertical.center];

        targetTileVertical.bottom = ((currentObject->x + 16 - HITBOX_OFFSET_RIGHT) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
    else
    {
        targetTileVertical.top = ((currentObject->x + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY + HITBOX_SIZE_Y + HITBOX_OFFSET_TOP) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.center = ((currentObject->x + 8) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY + HITBOX_SIZE_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.centerValue = hitmapPool[0][targetTileVertical.center];

        targetTileVertical.bottom = ((currentObject->x + 16 - HITBOX_OFFSET_RIGHT) / HITBOX_TILESIZE) + (((currentObject->y + currentObject->speedY + HITBOX_SIZE_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
}

BANKREF(checkCollisionObject)
bool checkCollisionObject(void) BANKED
{

    return hero.x + HITBOX_OFFSET_LEFT < enemy.x + ENEMY_BOSSDBG_HITBOX_OFFSET_LEFT + ENEMY_BOSSDBG_HITBOX_SIZE_X &&
           hero.x + HITBOX_SIZE_X + HITBOX_OFFSET_LEFT > enemy.x + ENEMY_BOSSDBG_HITBOX_OFFSET_LEFT &&
           hero.y + HITBOX_OFFSET_TOP < enemy.y + ENEMY_BOSSDBG_HITBOX_SIZE_Y + ENEMY_BOSSDBG_HITBOX_OFFSET_TOP &&
           hero.y + HITBOX_SIZE_Y + HITBOX_OFFSET_TOP > enemy.y + ENEMY_BOSSDBG_HITBOX_OFFSET_TOP;
}

BANKREF(checkCollisionHitbox)
bool checkCollisionHitbox(void) BANKED
{
    return heroAttackHitbox.x < enemy.x + ENEMY_BOSSDBG_HITBOX_OFFSET_LEFT + ENEMY_BOSSDBG_HITBOX_SIZE_X &&
           heroAttackHitbox.x + heroAttackHitbox.width > enemy.x + ENEMY_BOSSDBG_HITBOX_OFFSET_LEFT &&
           heroAttackHitbox.y < enemy.y + ENEMY_BOSSDBG_HITBOX_SIZE_Y &&
           heroAttackHitbox.y + heroAttackHitbox.height > enemy.y + ENEMY_BOSSDBG_HITBOX_OFFSET_TOP;
}