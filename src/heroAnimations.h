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
    //10, 2, 3, 11, __12, __13, 7, 14, 15, 0, 0, 0,
    10, 16, 17, 11, 18, 19, 7, 14, 15, 0, 0, 0,
    //20, 16, 17, 21, 22, 23, 7, 8, 9, 0, 0, 0,
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
    41, 42, 43, 44, 45, 46, 47, 48, 49, 0, 0, 0,
    0, 33, 34, /*35*/0, 36, 37, 38, 39, 40, 0, 0, 0, 
    24, 25, 26, 27, 28, 29, 30, 31, 32, 0, 0, 0,
    0, 33, 34, /*35*/0, 36, 37, 38, 39, 40, 0, 0, 0, 
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
    1, 2, 3, 4, 50, 51, 52, 53, 54, 55, 0, 0
};

const int8_t heroJumpingFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16, 5, 0, 0
};

const int8_t heroJumpingFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 16, 8, 0, 12, 0, 0
};

const int8_t heroJumpingFramesY[12] = {
    0, 0, 0, 8, 8, 8, 16, 16, 16, 24, 120, 120
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
    1, 57, 58, 4, 59, 60, 7, 61, 62, 0, 0, 0
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
    1, 57, 58, 4, 59, 60, 52, 53, 54, 55, 0, 0
};


/*  ----------------------
        UPPERCUT
    ---------------------- */
const int8_t *heroUppercutFrames[4] = {
    heroUppercutFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroJumpingFramesY,
};
    
const int8_t heroUppercutFramesTiles[1*12] = {
    12, 13, 20, 63, 28, 21, 22, 23, 35, 55, 0, 0
};

const int8_t heroUppercutFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16, 6, 0, 0
};

const int8_t heroUppercutFramesXLeft[12] = {
    16, 8, 0, 16, 8, 0, 16, 8, 0, 11, 0, 0
};

const int8_t *heroHurtFrames[4] = {
    heroHurtFramesTiles,
    heroJumpingFramesXLeft,
    heroJumpingFramesXRight,
    heroIdleFramesY,
};

const int8_t heroHurtFramesTiles[12] = {
    2, 2, 2, 1, 1, 1, 2, 2, 2,
};

#endif