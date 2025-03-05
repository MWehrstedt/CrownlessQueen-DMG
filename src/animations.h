#include <gbdk/platform.h>

#ifndef __ANIMATIONS_H__
#define __ANIMATIONS_H__

/*  ======================
            HERO
    ====================== */
static const int8_t *heroIdleFrames[4] = {
    heroIdleFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

static const int8_t heroIdleFramesXRight[9] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16,
};

static const int8_t heroIdleFramesXLeft[9] = {
    16, 8, 0, 16, 8, 0, 16, 8, 0,
};

static const int8_t heroIdleFramesY[9] = {
    0, 0, 0, 8, 8, 8, 16, 16, 16,
};

static const int8_t heroIdleFramesTiles[9] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static const int8_t *heroJumpingFrames[4] = {
    heroIdleFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroIdleFramesY,
};

static const int8_t heroJumpingFramesXRight[9] = {
    -4, 8, 20, -4, 8, 20, -4, 8, 20,
};

static const int8_t heroJumpingFramesXLeft[9] = {
    20, 8, -4, 20, 8, -4, 20, 8, -4,
};

static const int8_t *heroHurtFrames[4] = {
    heroHurtFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroIdleFramesY,
};

static const int8_t heroHurtFramesTiles[9] = {
    2, 2, 2, 1, 1, 1, 2, 2, 2,
};


/*  ======================
            BOSS_DBG
    ====================== */
    
static const int8_t *bossDbgFrames[4] = {
    bossDbgTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

static const int8_t bossDbgTiles[9] = {
    2, 3, 2, 3, 1, 3, 2, 1, 2,
};

#endif