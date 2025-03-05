#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__
#include "types.h"
#include <gbdk/platform.h>

/// @brief Don't do anything.
static const uint8_t *dummyStrategy[1] = {
    dummyPlan,
};

static const uint8_t dummyPlan[1] = {
    0,
};

static const uint8_t *bossDbgStrategies[1] = {
    bossDbgPlan1,
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

#endif