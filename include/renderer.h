#pragma once

#include <raylib.h>
#include "simulation.h"

#define DELTA_THETA 0.09f
#define DELTA_POS 0.09f

void cam_update(Camera3D *camera);
void render(SimState *state);