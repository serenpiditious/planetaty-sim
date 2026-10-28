#pragma once
#include <math.h>
#include "../include/simulation.h"

// Two equal stars orbit their common centre while the whole system drifts
// along +Y. Seen from the side, each trail is a helix, together a double helix.

#ifndef TRAIL_ALPHA
#define TRAIL_ALPHA 210
#endif

#define BS_COL_A   255, 150,  50
#define BS_COL_B    60, 230, 255

#define BS_MASS    1000000.0f   // mass of each star
#define BS_SEP     1000.0f      // distance between the two stars
#define BS_RADIUS  60.0f
#define BS_DRIFT   150.0f       // speed along +Y. Higher = more stretched helix

SimState binarystar(){
	// speed for a perfectly circular orbit of two equal masses:
	// each star orbits at radius SEP/2 with acceleration G*m/SEP^2
	// v^2 = a * r  =>  v = sqrt(G*m / (2*SEP))
	float orbit_v = sqrtf(G * BS_MASS / (2.0f * BS_SEP));

	Planet StarA = {.position = {BS_SEP / 2.0f, 0.0f, 0.0f},
		.velocity = {0.0f, BS_DRIFT, orbit_v},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = BS_RADIUS,
		.mass = BS_MASS,
		.trailColor = {BS_COL_A, TRAIL_ALPHA},
		.history = {0},
		.label = "BARR",
		.planetColor = {BS_COL_A, 255}};
	Planet StarB = {.position = {-BS_SEP / 2.0f, 0.0f, 0.0f},
		.velocity = {0.0f, BS_DRIFT, -orbit_v},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = BS_RADIUS,
		.mass = BS_MASS,
		.trailColor = {BS_COL_B, TRAIL_ALPHA},
		.history = {0},
		.label = "FOOO",
		.planetColor = {BS_COL_B, 255}};

	// static: the array must outlive this function, because state.planets
	// points at it. A normal local array would be gone after the return.
	static Planet planets[2];
	planets[0] = StarA;
	planets[1] = StarB;
	int planet_num = 2;

	// start every trail at the star's starting position
	for (int i = 0; i < planet_num; i++){
		for (int j = 0; j < TRAIL_SIZE; j++){
			planets[i].history[j] = planets[i].position;
		}
		planets[i].HeadIndex = 0;
	}

	SimState state = {0};
	Camera3D camera = {
		.position = (Vector3){ 0.0f, 0.0f, -4500.0f },  // side view, helix rises upwards
		.target = (Vector3){0.0f, 800.0f, 0.0f},
		.up = (Vector3){ 0.0f, 1.0f, 0.0f },
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};
	state.planet_num = planet_num;
	state.planets = planets;
	state.camera = camera;
	state.isPaused = 0;
	state.cameraState = 0;

	return state;
}
