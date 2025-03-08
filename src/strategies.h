#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__
#include "types.h"
#include <gbdk/platform.h>

/// @brief Don't do anything.
static const uint8_t *dummyStrategy[1] = {
    dummyPlan,
};

static const uint8_t dummyPlan[5] = {
    0,
    0,
    0,
    0,
    0,
};

static const uint8_t *bossDbgStrategies[2] = {
    bossDbgPlan1,
    bossDbgPlan2,
};

static const uint8_t bossDbgPlan1[40] = {
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

static const uint8_t bossDbgPlan2[20] = {
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

#endif