#pragma once
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include "../include/simulation.h"

// N equal stars on a ring, all orbiting the centre in the same direction.
// Optional massive star in the middle (NS_CENTER 1). The ring is only
// stable with a heavy central star; with NS_CENTER 0 it is a pure ring that
// slowly falls apart, which is also fun to watch.
// NS_DRIFT moves the whole system along +Y so every trail becomes a helix.

#ifndef TRAIL_ALPHA
#define TRAIL_ALPHA 210
#endif

#define NS_COUNT         5          // number of ring stars
#define NS_CENTER        1          // 1 = star in the middle, 0 = none
#define NS_RING_RADIUS   1500.0f
#define NS_MASS          50000.0f   // mass of each ring star
#define NS_RADIUS        80.0f
#define NS_CENTRAL_MASS  5000000.0f
#define NS_CENTRAL_RADIUS 250.0f
#define NS_DRIFT         120.0f     // speed along +Y, 0 = flat system

#define NS_TOTAL (NS_COUNT + NS_CENTER)

SimState nstar(){
	static Planet planets[NS_TOTAL];   // static: must outlive this function
	static char names[NS_TOTAL][16];   // label text must outlive it too

	float R = NS_RING_RADIUS;
	float central_mass = NS_CENTER ? NS_CENTRAL_MASS : 0.0f;

	// inward acceleration on one ring star:
	//   from the centre:       G*M / R^2
	//   from the other N-1:    G*m / (4R^2) * sum_k 1/sin(pi*k/N)
	// circular orbit needs v^2 / R = that acceleration
	float sum = 0.0f;
	for (int k = 1; k < NS_COUNT; k++){
		sum += 1.0f / sinf(PI * k / NS_COUNT);
	}
	float acc = G * central_mass / (R * R) + G * NS_MASS * sum / (4.0f * R * R);
	float orbit_v = sqrtf(acc * R);

	for (int i = 0; i < NS_COUNT; i++){
		float theta = 2.0f * PI * i / NS_COUNT;
		// every star gets its own hue around the colour wheel
		Color c = ColorFromHSV(360.0f * i / NS_COUNT, 0.75f, 1.0f);
		Color trail = c;
		trail.a = TRAIL_ALPHA;

		snprintf(names[i], sizeof names[i], "Star %d", i + 1);

		planets[i] = (Planet){
			.label = names[i],
			.position = {R * cosf(theta), 0.0f, R * sinf(theta)},
			// tangent direction (counter-clockwise), plus the drift
			.velocity = {-orbit_v * sinf(theta), NS_DRIFT, orbit_v * cosf(theta)},
			.acceleration = {0.0f, 0.0f, 0.0f},
			.radius = NS_RADIUS,
			.mass = NS_MASS,
			.trailColor = trail,
			.planetColor = c,
		};
	}

#if NS_CENTER
	Color cc = {255, 225, 80, 255};
	Color ct = cc;
	ct.a = TRAIL_ALPHA;
	planets[NS_COUNT] = (Planet){
		.label = "Center",
		.position = {0.0f, 0.0f, 0.0f},
		.velocity = {0.0f, NS_DRIFT, 0.0f},   // drifts with the rest
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = NS_CENTRAL_RADIUS,
		.mass = NS_CENTRAL_MASS,
		.trailColor = ct,
		.planetColor = cc,
	};
#endif

	// start every trail at the body's starting position
	for (int i = 0; i < NS_TOTAL; i++){
		for (int j = 0; j < TRAIL_SIZE; j++){
			planets[i].history[j] = planets[i].position;
		}
		planets[i].HeadIndex = 0;
	}

	SimState state = {0};
	Camera3D camera = {
		.position = (Vector3){ 0.0f, 2500.0f, -5000.0f },
		.target = (Vector3){0.0f, 500.0f, 0.0f},
		.up = (Vector3){ 0.0f, 1.0f, 0.0f },
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};
	state.planet_num = NS_TOTAL;
	state.planets = planets;
	state.camera = camera;
	state.isPaused = 0;
	state.cameraState = 0;

	return state;
}
