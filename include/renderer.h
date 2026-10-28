#pragma once

#include <raylib.h>
#include <rlgl.h>
#include "simulation.h"
//#include "gui.h"


#define DELTA_THETA 180.0f
#define DELTA_POS 1000.0f

void drawTrail(Planet *planet);
void target_cam(SimState *state);
void cam_update(SimState *state);
void render(SimState *state);
