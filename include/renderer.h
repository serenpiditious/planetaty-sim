#pragma once

#include <raylib.h>
#include "simulation.h"

#define DELTA_THETA 180.0f
#define DELTA_POS 250.0f

void cam_update(SimState *state);
void render(SimState *state);
