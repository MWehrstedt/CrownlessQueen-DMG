#ifndef __TYPES_H__
#define __TYPES_H__
#include "../include/stdint.h"

#define GAME_GRAVITY_MAX	5
#define GAME_GRAVITY_STEP	1
#define GAME_FRICTION		1

#define HITBOX_MAPSIZE_X 16
#define HITBOX_MAPSIZE_Y 9
#define HITBOX_OFFSET_LEFT	2
#define HITBOX_SIZE_X 12
#define HITBOX_SIZE_Y 20
#define HITBOX_TILESIZE 16

#define HERO_JUMP_SPEED			(-12)
#define HERO_DIRECTION_RIGHT 	0b00000001
#define HERO_DIRECTION_DOWN 	0b00000010
#define HERO_DIRECTION_LEFT 	0b00000100
#define HERO_DIRECTION_UP 		0b00001000
#define HERO_STATE_GROUNDED		0b1000000
#define HERO_STATE_JUMPING		0b0100000
#define HERO_WALK_SPEED			(2)

typedef struct
{
	uint8_t x;
	uint8_t y;
	int8_t speedX;
	int8_t speedY;
	uint8_t drawX;
	uint8_t drawY;
	uint8_t state;
	uint8_t direction;
} hero_t;

typedef struct
{
    uint8_t bottom;
    uint8_t center;
    uint8_t top;
	uint8_t centerValue;
} targetTile_t;


#endif // !__TYPES_H__
