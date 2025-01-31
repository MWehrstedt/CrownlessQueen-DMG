// #include <gb/gb.h>
#include <gbdk/platform.h>
#include <stdint.h>
#include "vars.h"
#include "hero.h"
#include "collision.h"
#include "../include/hitmapsPool.h"

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
    if (hero.speedX < 0)
    {
        targetTileHorizontal.top = ((hero.x + hero.speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + ((hero.y / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.center = ((hero.x + hero.speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((hero.y + 12) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.centerValue = hitmapPool[0][targetTileHorizontal.center];

        targetTileHorizontal.bottom = ((hero.x + hero.speedX + HITBOX_OFFSET_LEFT) / HITBOX_TILESIZE) + (((hero.y + 24) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
    else
    {
        targetTileHorizontal.top = ((hero.x + hero.speedX + HITBOX_SIZE_X) / HITBOX_TILESIZE) + ((hero.y / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.center = ((hero.x + hero.speedX + HITBOX_SIZE_X) / HITBOX_TILESIZE) + (((hero.y + 12) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileHorizontal.centerValue = hitmapPool[0][targetTileHorizontal.center];

        targetTileHorizontal.bottom = ((hero.x + hero.speedX + HITBOX_SIZE_X) / HITBOX_TILESIZE) + (((hero.y + 24) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
}

BANKREF(checkCollisionBackgroundY)
void checkCollisionBackgroundY(void) BANKED
{

    // Get tile collisions for hero
    if (hero.speedY < 0)
    {
        targetTileVertical.top = (hero.x / HITBOX_TILESIZE) + (((hero.y + hero.speedY) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.center = ((hero.x + 8) / HITBOX_TILESIZE) + (((hero.y + hero.speedY) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.centerValue = hitmapPool[0][targetTileVertical.center];

        targetTileVertical.bottom = ((hero.x + 16) / HITBOX_TILESIZE) + (((hero.y + hero.speedY) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
    else
    {
        targetTileVertical.top = (hero.x / HITBOX_TILESIZE) + (((hero.y + hero.speedY + HITBOX_SIZE_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.center = ((hero.x + 8) / HITBOX_TILESIZE) + (((hero.y + hero.speedY + HITBOX_SIZE_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
        targetTileVertical.centerValue = hitmapPool[0][targetTileVertical.center];

        targetTileVertical.bottom = ((hero.x + 16) / HITBOX_TILESIZE) + (((hero.y + hero.speedY + HITBOX_SIZE_Y) / HITBOX_TILESIZE) * HITBOX_MAPSIZE_X);
    }
}
