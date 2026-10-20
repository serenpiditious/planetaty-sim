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

#include "./include/simulation.h"
#include "./include/renderer.h"

#define WIN_WIDTH 1500
#define WIN_HEIGHT 700
// coefficient of restitution
#define E 1

int main(){
	Planet earth = {.position = {0.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 20.0f,
		.mass = 10000};
	Planet jupiter = {.position = {250.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 60.0f,
		.mass = 15000};
	Planet eridani = {.position = {0.0f, 300.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 20.0f,
		.mass = 100000};
	
	int planet_num = 1;
	Planet planets[] = {earth, jupiter, eridani};

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
	while (!WindowShouldClose()){
		state.deltaTime = GetFrameTime();
		SetMousePosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);

		physics(&state, E);
		render(&state);
	}
}
