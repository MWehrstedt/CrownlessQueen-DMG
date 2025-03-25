#include <gbdk/platform.h>
#include "types.h"
#include "strategies.h"

#pragma bank 255

const uint8_t *dummyStrategy[1] = {
    dummyPlan,
};

const uint8_t dummyPlan[5] = {
    0,
    0,
    0,
    0,
    0,
};

const uint8_t *bossDbgStrategies[2] = {
    bossDbgPlan1,
    bossDbgPlan2,
};

const uint8_t bossDbgPlan1[40] = {
    J_A,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
};

const uint8_t bossDbgPlan2[20] = {
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_LEFT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
    J_RIGHT,
};
