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
#include "solar_system.c"
#include "./include/raygui.h"
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
// coefficient of restitution
#define E 1

int main(){

	int planet_num = 9;
	Planet planets[] = {Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune};

	Vector3 move_speed = {0.5f, 0.5f, 0.5f};

	Camera3D camera = {
		.position = (Vector3){ 0.0f, 0.0f, -500.0f },  // Camera position
		.target = (Vector3){0.0f, 0.0f, 0.0f},      // Camera looking at point
		.up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
		.fovy = 45.0f,                                // Camera field-of-view Y
		.projection = CAMERA_PERSPECTIVE
	};

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Planetary Sim");

	DisableCursor();
	SetTargetFPS(1000);

	SimState state;
	state.planet_num = planet_num;
	state.planets = planets;
	state.camera = camera;
	state.isPaused = 0;
	state.cameraState = 0;

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
