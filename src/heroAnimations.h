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
    1, 61, 62, 10, 11, 12, 7, 13, 14, 0, 0, 0,
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
    0, 15, 16, 17, 18, 19, 20, 21, 22, 0, 0, 0,
    0, 23, 24, 0, 25, 26, 27, 28, 29, 0, 0, 0, 
    0, 30, 31, 32, 33, 34, 35, 36, 37, 0, 0, 0,
    0, 23, 24, 0, 25, 26, 27, 28, 29, 0, 0, 0, 
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
    1, 2, 3, 4, 38, 39, 40, 41, 0, 42, 0, 0
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
    1, 43, 44, 45, 46, 47, 7, 48, 49, 0, 0, 0,
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
    1, 43, 44, 45, 46, 47, 40, 41, 0, 42, 0, 0,
};


/*  ----------------------
        UPPERCUT
    ---------------------- */
const int8_t *heroUppercutFrames[4] = {
    heroUppercutFramesTiles,
    heroUppercutFramesXLeft,
    heroUppercutFramesXRight,
    heroJumpingFramesY,
};
    
const int8_t heroUppercutFramesTiles[1*12] = {
    50, 51, 52, 53, 18, 54, 55, 56, 57, 42, 0, 0
};

const int8_t heroUppercutFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16, 6, 0, 0
};

const int8_t heroUppercutFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 16, 8, 0, 10, 0, 0
};

const int8_t *heroHurtFrames[4] = {
    heroHurtFramesTiles,
    heroIdleFramesXLeft,
    heroIdleFramesXRight,
    heroIdleFramesY,
};

const int8_t heroHurtFramesTiles[12] = {
    1, 58, 59, 4, 46, 60, 7, 48, 49, 0, 0, 0,
};

#endif