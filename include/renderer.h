#pragma once

#include <raylib.h>
#include "simulation.h"

#define DEG_TO_RAD PI/180
#define DELTA_THETA 0.03f
#define DELTA_POS 0.09f

void cam_update(Camera3D *camera);
void render(SimState *state);