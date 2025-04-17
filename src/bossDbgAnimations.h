#ifndef __BOSSDBGANIMATIONS_H__
#define __BOSSDBGANIMATIONS_H__


/*  ======================
            BOSS_DBG
    ====================== */

/*  ----------------------
            IDLE
    ---------------------- */
const int8_t *bossDbgIdleFrames[4] = {
    bossDbgIdleTiles,
    bossDbgIdleFramesXRight,
    bossDbgIdleFramesXRight,
    bossDbgIdleFramesY,
};
    
const int8_t bossDbgIdleFramesXRight[12] = {
    0, 8, 16, 0, 8, 16, 0, 8, 16, 120, 120, 120
};

const int8_t bossDbgIdleFramesY[12] = {
    0, 0, 0, 8, 8, 8, 16, 16, 16, 120, 120, 120
};

const int8_t bossDbgIdleTiles[12] = {
    80, 81, 0, 82, 83, 0, 84, 85, 0, 0, 0, 0, 
};


/*  ----------------------
            HURT
    ---------------------- */

const int8_t *bossDbgHurtFrames[4] = {
    bossDbgHurtTiles,
    bossDbgIdleFramesXRight,
    bossDbgIdleFramesXRight,
    bossDbgIdleFramesY,
};

const int8_t bossDbgHurtTiles[12] = {
    80, 81, 0, 86, 87, 0, 88, 89, 0, 0, 0, 0, 
};
#endif