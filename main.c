// TODO: energy conservation
// TODO: units - S/L
// TODO: isStationary - S/L
// TODO: GUI - S

#include <stdio.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./include/simulation.h"
#include "./include/renderer.h"
#include "./include/raygui.h"

#include "./examples/solar_system.h"
#include "./examples/binary_star.h"
#include "./examples/solar_system_moons.h"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
// coefficient of restitution
#define E 1

int main(){
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Planetary Sim");

	DisableCursor();
	SetTargetFPS(200);

	SimState state = solarsystem_moons();

	for( int i = 0; i<state.planet_num; i++){
		for(int j = 0; j<TRAIL_SIZE; j++){
			state.planets[i].history[j] = state.planets[i].position;
		}
	}

	GuiSetStyle(DEFAULT,TEXT_SIZE,30);
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));
	GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));


	while (!WindowShouldClose()){
		state.deltaTime = GetFrameTime();

		if(!state.isPaused){
			physics(&state, E);
		}
		if(IsKeyPressed(KEY_P)){
			state.isPaused = !state.isPaused;
			if(state.isPaused) EnableCursor();
			else DisableCursor();
		}

		render(&state);

	}
}
