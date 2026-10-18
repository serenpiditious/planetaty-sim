#pragma once
#include <raylib.h>
#include "simulation.h"

typedef struct {
	Planet *planets;
	
}SimState;

int render(SimState state);
