#ifndef __HEROANIMATIONS_H__
#define __HEROANIMATIONS_H__

const int8_t *heroIdleFrames[4] = {
    heroIdleFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

const int8_t heroIdleFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16, 120, 120, 120
};

const int8_t heroIdleFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 16, 8, 0, 120, 120, 120
};

const int8_t heroIdleFramesY[12] = {
    0, 0, 0, 8, 8, 8, 16, 16, 16, 120, 120, 120
};

const int8_t heroIdleFramesTiles[2*12] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0,
    10, 11, 12, 13, 14, 15, 7, 16, 17, 0, 0, 0,
};

/*  ----------------------
            WALKING
    ---------------------- */
const int8_t *heroWalkingFrames[4] = {
    heroWalkingFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

const int8_t heroWalkingFramesTiles[4*12] = {
    0, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0,
    0, 26, 27, 0, 28, 29, 30, 31, 32, 0, 0, 0, 
    0, 33, 34, 10, 35, 36, 37, 38, 39, 0, 0, 0,
    0, 26, 27, 0, 28, 29, 30, 31, 32, 0, 0, 0, 
};

/*  ----------------------
            JUMPING
    ---------------------- */

const int8_t *heroJumpingFrames[4] = {
    heroJumpingFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroJumpingFramesY,
};

const int8_t heroJumpingFramesTiles[1*12] = {
    1, 2, 3, 4, 40, 41, 42, 43, 0, 44, 0, 0
};

const int8_t heroJumpingFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 1, 9, 17, 4, 0, 0
};

const int8_t heroJumpingFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 17, 9, 1, 14, 0, 0
};

const int8_t heroJumpingFramesY[12] = {
    0, 0, 0, 8, 8, 8, 16, 16, 120, 24, 120, 120
};

/*  ----------------------
        STANDING ATTACK
    ---------------------- */
const int8_t *heroAttackFrames[4] = {
    heroAttackFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};
    
const int8_t heroAttackFramesTiles[1*12] = {
    1, 45, 46, 4, 47, 48, 7, 49, 50, 0, 0, 0,
};

/*  ----------------------
        JUMPING ATTACK
    ---------------------- */
const int8_t *heroJumpingAttackFrames[4] = {
    heroJumpingAttackFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroJumpingFramesY,
};
    
const int8_t heroJumpingAttackFramesTiles[1*12] = {
    1, 45, 46, 4, 47, 48, 42, 43, 0, 44, 0, 0,
};


/*  ----------------------
        UPPERCUT
    ---------------------- */
const int8_t *heroUppercutFrames[4] = {
    heroUppercutFramesTiles,
    heroUppercutFramesXLeft,
    heroUppercutFramesXRight,
    heroUppercutFramesY,
};
    
const int8_t heroUppercutFramesTiles[1*12] = {
    51, 52, 53, 54, 21, 55, 56, 57, 0, 44, 0, 0
};

const int8_t heroUppercutFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 4, 12, 0, 6, 0, 0
};

const int8_t heroUppercutFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 12, 4, 0, 10, 0, 0
};

const int8_t heroUppercutFramesY[12] = {
    0, 0, 0, 8, 8, 8, 16, 16, 120, 24, 120, 120
};

const int8_t *heroHurtFrames[4] = {
    heroHurtFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

const int8_t heroHurtFramesTiles[12] = {
    1, 58, 59, 4, 47, 60, 7, 61, 62, 0, 0, 0,
};

/*  ----------------------
        Side Step
    ---------------------- */
const int8_t *heroSideStepFrames[4] = {
    heroSideStepFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

const int8_t heroSideStepFramesTiles[12] = {
    0, 63, 64, 20, 21, 65, 66, 67, 68, 0, 0, 0,
};
#endif