// TODO: camera - S
// TODO: units - S/L
// TODO: isStationary - S/L
// TODO: GUI - S
// TODO: Skybox - S
// TODO: Trail - L
// TODO: textures - S/L

#include <stdio.h>
#include <math.h>

#include <raylib.h>
#include "./include/simulation.h"
#include "./include/renderer.h"

int main(){
	Planet earth = {.position = {100.0f, 50.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {-30.0f, -15.0f, 0.0f},
		.radius = 20.0f,
		.mass = 10000};
	Planet jupiter = {.position = {250.0f, 0.0f, 0.0f},
		.velocity = {-50.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 60.0f,
		.mass = 15000};
	Planet eridani = {.position = {0.0f, 300.0f, 0.0f},
		.velocity = {0.0f, -10.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 20.0f,
		.mass = 100000};
	
	int planet_num = 3;
	Planet planets[] = {earth, jupiter, eridani};
	
	const int win_width = 1500;
	const int win_height = 700;
	float e = 1; // coefficient of restitution

	Camera3D camera = {
		.position = (Vector3){ 0.0f, 0.0f, -500.0f },  // Camera position
    	.target = (Vector3){0.0f, 0.0f, 0.0f},      // Camera looking at point
    	.up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
    	.fovy = 45.0f,                                // Camera field-of-view Y
    	.projection = CAMERA_PERSPECTIVE
	};

	InitWindow(win_width, win_height, "Planetary Sim");

	SetTargetFPS(240);

	SimState state;
	while (!WindowShouldClose()){
		float deltaTime = GetFrameTime();
		UpdateCamera(&camera, CAMERA_FREE);

		state.camera = camera;
		state.planets = planets;
		state.deltaTime = deltaTime;
		state.planet_num = planet_num;

		physics(state, e);
		render(state);
	}
}
