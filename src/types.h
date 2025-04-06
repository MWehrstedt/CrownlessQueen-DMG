#ifndef __TYPES_H__
#define __TYPES_H__
#include "../include/stdint.h"
#include "../include/stdbool.h"
#include <gbdk/platform.h>

/*  ======================
			DEFINES
	====================== */
#define ENEMY_BOSSDBG_HITBOX_OFFSET_LEFT (-1)
#define ENEMY_BOSSDBG_HITBOX_OFFSET_TOP 1
#define ENEMY_BOSSDBG_HITBOX_OFFSET_RIGHT 5
#define ENEMY_BOSSDBG_HITBOX_OFFSET_BOTTOM 0
#define ENEMY_BOSSDBG_HITBOX_SIZE_X 15
#define ENEMY_BOSSDBG_HITBOX_SIZE_Y 23

#define GAME_GRAVITY_MAX 5
#define GAME_GRAVITY_STEP 1
#define GAME_FRICTION 1
#define GAME_MODE_SINGLE 0b00000001
#define GAME_MODE_MULTI 0b00000010
#define GAME_STATE_INTRO 0b00000001
#define GAME_STATE_MAINMENU 0b00000010
#define GAME_STATE_GAMEPLAY 0b00000011
#define GAME_STATE_INITGAMEPLAY 0b00000100
#define GAME_STATE_PAUSED 0b10000000

#define HITBOX_ACTIVE 0b00000001
#define HITBOX_MAPSIZE_X 10
#define HITBOX_MAPSIZE_Y 9
#define HITBOX_TILESIZE 16

#define HITBOX_OFFSET_LEFT 5
#define HITBOX_OFFSET_TOP 1
#define HITBOX_OFFSET_RIGHT 0
#define HITBOX_OFFSET_BOTTOM 0
#define HITBOX_SIZE_X 14
#define HITBOX_SIZE_Y 23

#define HERO_ATTACK_PUNCH_TWO 0b00000010

#define HERO_CURRENT_ATTACK_NONE (255)
#define HERO_ATTACK_PUNCH_ONE (0b00000000)
#define HERO_ATTACK_UPPERCUT (0b00000001)
#define HERO_ATTACK_SIDESTEP (0b00000010)
#define HERO_ATTACK_DASH (0b00000011)
#define HERO_ATTACK_DEMON (0b00100000)

#define HERO_TIMER_HURT (50)
#define HERO_TIMER_INVULNERABILITY (60)
#define HERO_TIMER_SIDESTEP_MAX (8)
#define HERO_KNOCKBACK_VERTICAL (-5)
#define HERO_KNOCKBACK_HORIZONTAL (2)

#define HERO_JUMP_SPEED (-11)
#define HERO_UPPERCUT_JUMP_SPEED (-8)
#define HERO_UPPERCUT_VERTICALSPEED (-13)
#define HERO_UPPERCUT_HORIZONTALSPEED (2)
#define HERO_SIDESTEP_SPEED (7)
#define HERO_DASH_SPEED (10)
#define HERO_DIRECTION_RIGHT 0b00000001
#define HERO_DIRECTION_DOWN 0b00000010
#define HERO_DIRECTION_LEFT 0b00000100
#define HERO_DIRECTION_UP 0b00001000
#define HERO_STATE_GROUNDED 0b10000000
#define HERO_STATE_JUMPING 0b01000000
#define HERO_STATE_CHARGING 0b00100000
#define HERO_STATE_ATTACKING 0b00010000
#define HERO_STATE_HURT 0b00001000
#define HERO_STATE_DOWNCHARGING 0b00000100
#define HERO_STATE_WALKING 0b00000010
#define HERO_WALK_SPEED (2)

#define OAM_HERO_SPRITEID (0)
#define OAM_ENEMY_SPRITEID (20)

#define WND_BLANK_TILE_ID (100)
#define WND_NOHEALTH_TILE_ID (105)

// Platform specific defines
#if defined(GAMEBOY)
#define WND_HEALTH_OFFET_Y (0)
#else
#define WND_HEALTH_OFFET_Y (15)
#endif

/*  ======================
			TYPEDEFS
	====================== */
typedef struct
{
	bool human;
	bool animationPlay;
	uint8_t x;
	uint8_t y;
	int8_t speedX;
	int8_t speedY;
	uint8_t animationCounter;
	uint8_t attackChargeCounter;
	uint8_t buttonIndex;
	uint8_t drawCounter;
	uint8_t drawIndex;
	uint8_t drawFrameLength;
	uint8_t drawFrameRate;
	uint8_t drawX;
	uint8_t drawY;
	uint8_t health;
	uint8_t maxHealth;
	uint8_t state;
	uint8_t direction;
	uint8_t currentAttack;
	uint8_t invulnerability;
	uint8_t stateCounter;
	uint8_t strategyIndex;
	void (*handleInput)(void);
	void (*update)(void);
	void (*draw)(void);
	const uint8_t **strategy;
	const int8_t **drawFrames;
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
	uint8_t offsetX;
	uint8_t offsetY;
	uint8_t width;
	uint8_t height;
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
