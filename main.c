// TODO: energy conservation
// TODO: units - S/L
// TODO: isStationary - S/L
// TODO: GUI - S
// TODO: Skybox - S
// TODO: Trail - L
// TODO: textures - S/L

#include <stdio.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./include/simulation.h"
#include "./include/renderer.h"
#include "solar_system.c"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
// coefficient of restitution
#define E 1

int main(){
        Planet eridani = {.position = {0.0f, 300.0f, 0.0f},
                .velocity = {0.0f, 0.0f, 0.0f},
                .acceleration = {0.0f, 0.0f, 0.0f},
                .radius = 20.0f,
                .trailColor = WHITE,
                .history = {0},
                .isStationary = 0,
                .planetColor = MAROON,
                .mass = 100000};
	
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

	HideCursor();
	SetTargetFPS(480);

	SimState state;
	state.planet_num = planet_num;
	state.planets = planets;
	state.camera = camera;
	
	int mouse_update = 0;
	while (!WindowShouldClose()){
		state.deltaTime = GetFrameTime();

		physics(&state, E);
		render(&state);
		if (mouse_update % 8 == 0){
			SetMousePosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
		}
		mouse_update += 1;
	}
}
