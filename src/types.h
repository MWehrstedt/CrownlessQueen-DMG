#ifndef __TYPES_H__
#define __TYPES_H__
#include "../include/stdint.h"

#define GAME_GRAVITY_MAX 5
#define GAME_GRAVITY_STEP 1
#define GAME_FRICTION 1
#define GAME_STATE_INTRO	0b00000001
#define GAME_STATE_MAINMENU 0b00000010
#define GAME_STATE_GAMEPLAY 0b00000011
#define GAME_STATE_PAUSED	0b10000000

#define HITBOX_ACTIVE 0b00000001
#define HITBOX_MAPSIZE_X 16
#define HITBOX_MAPSIZE_Y 9
#define HITBOX_OFFSET_LEFT 2
#define HITBOX_OFFSET_TOP 2
#define HITBOX_OFFSET_RIGHT 2
#define HITBOX_OFFSET_BOTTOM 0
#define HITBOX_SIZE_X 20
#define HITBOX_SIZE_Y 20
#define HITBOX_TILESIZE 16

#define HERO_ATTACK_PUNCH_ONE 0b00000001
#define HERO_ATTACK_PUNCH_TWO 0b00000010
#define HERO_ATTACK_JPUNCH_ONE 0b01000001
#define HERO_ATTACK_JPUNCH_TWO 0b01000010

#define HERO_ATTACK_UPPERCUT 0b00000100
#define HERO_ATTACK_JUPPERCUT 0b01000100
#define HERO_ATTACK_DASH_LEFT 0b00001000
#define HERO_ATTACK_DASH_RIGHT 0b00010000
#define HERO_ATTACK_DEMON 0b00100000

#define HERO_JUMP_SPEED (-11)
#define HERO_UPPERCUT_JUMP_SPEED (-8)
#define HERO_DIRECTION_RIGHT 0b00000001
#define HERO_DIRECTION_DOWN 0b00000010
#define HERO_DIRECTION_LEFT 0b00000100
#define HERO_DIRECTION_UP 0b00001000
#define HERO_STATE_GROUNDED 0b10000000
#define HERO_STATE_JUMPING 0b01000000
#define HERO_STATE_CHARGING 0b00100000
#define HERO_STATE_ATTACKING 0b00010000
#define HERO_WALK_SPEED (2)

#define SPRITES_HERO_ID (0)

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
	uint8_t currentAttack;
	void (*handleInput)(void);
	void (*update)(void);
	void (*draw)(void);
} character_t;

typedef struct
{
	uint8_t bottom;
	uint8_t center;
	uint8_t top;
	uint8_t centerValue;
} targetTile_t;

typedef struct
{
	uint8_t mode;
	uint8_t selectedSpecials;
	uint8_t state;
} game_t;

typedef struct
{
	uint8_t x;
	uint8_t y;
	uint8_t drawX;
	uint8_t drawY;
	uint8_t attribute;
	uint8_t counter;
	uint8_t damage;
} hitbox_t;

typedef struct
{
	uint8_t type;
	uint8_t damage;
	uint8_t startup;
	uint8_t recovery;
	uint8_t length;
} move_t;

#endif // !__TYPES_H__
