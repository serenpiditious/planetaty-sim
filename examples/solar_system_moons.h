#pragma once
#include <math.h>
#include <string.h>
#include <raylib.h>
#include "../include/simulation.h"

// Solar system with moons: Earth (1), Jupiter (4), Saturn (1).
//
// This is NOT the same numbers as solar_system.h. With those masses a planet's
// Hill sphere (the region where its gravity beats the Sun's) is smaller than
// the planet itself, so no moon could ever stay in orbit. Here the Sun is
// lighter and the planets heavier relative to it, and the planets are far
// enough apart, so every moon sits inside ~0.35 of its planet's Hill radius,
// where orbits are stable.

#ifndef TRAIL_ALPHA
#define TRAIL_ALPHA 210
#endif

#define MS_SUN_MASS    2500000.0f
#define MS_SUN_RADIUS  300.0f

#define MS_COL_SUN      ((Color){255, 225,  80, 255})
#define MS_COL_MERCURY  ((Color){  0, 255, 200, 255})
#define MS_COL_VENUS    ((Color){255,  90, 200, 255})
#define MS_COL_EARTH    ((Color){ 90, 160, 255, 255})
#define MS_COL_MOON     ((Color){210, 225, 255, 255})
#define MS_COL_MARS     ((Color){255,  70,  90, 255})
#define MS_COL_JUPITER  ((Color){255, 150,  50, 255})
#define MS_COL_IO       ((Color){255, 235, 120, 255})
#define MS_COL_EUROPA   ((Color){255, 205, 160, 255})
#define MS_COL_GANYMEDE ((Color){255, 175,  95, 255})
#define MS_COL_CALLISTO ((Color){255, 125,  75, 255})
#define MS_COL_SATURN   ((Color){190, 110, 255, 255})
#define MS_COL_TITAN    ((Color){225, 175, 255, 255})
#define MS_COL_URANUS   ((Color){ 60, 230, 255, 255})
#define MS_COL_NEPTUNE  ((Color){110,  90, 255, 255})

#define MS_TOTAL 15   // Sun + 8 planets + 6 moons

// fills one body from scratch (zeroes everything, trail starts at its position)
static void ms_body(Planet *p, const char *label, Vector3 pos, Vector3 vel,
                    float radius, float mass, Color c){
	memset(p, 0, sizeof(Planet));
	p->label = label;
	p->position = pos;
	p->velocity = vel;
	p->radius = radius;
	p->mass = mass;
	p->planetColor = c;
	p->trailColor = c;
	p->trailColor.a = TRAIL_ALPHA;
	for (int j = 0; j < TRAIL_SIZE; j++){
		p->history[j] = pos;
	}
	p->HeadIndex = 0;
}

// planet on a circular orbit around the Sun (Sun at the origin).
// angle_deg = where on the orbit it starts. returns its index.
static int ms_planet(Planet *planets, int *n, const char *label, float a,
                     float angle_deg, float radius, float mass, Color c){
	float phi = angle_deg * DEG2RAD;
	float v = sqrtf(G * (MS_SUN_MASS + mass) / a);
	Vector3 pos = {a * cosf(phi), 0.0f, a * sinf(phi)};
	Vector3 vel = {-v * sinf(phi), 0.0f, v * cosf(phi)};
	ms_body(&planets[*n], label, pos, vel, radius, mass, c);
	return (*n)++;
}

// moon on a circular orbit around planets[parent].
// d = distance from the planet, phase_deg = start position on its orbit,
// incl_deg = tilt of the orbit plane. The moon's speed is the planet's own
// velocity plus the speed needed for a circular orbit around it.
static void ms_moon(Planet *planets, int *n, int parent, const char *label,
                    float d, float phase_deg, float incl_deg,
                    float radius, float mass, Color c){
	Planet *P = &planets[parent];
	float phi = phase_deg * DEG2RAD;
	float inc = incl_deg * DEG2RAD;

	// orbit plane is spanned by u (along x) and w (tilted towards z/y)
	Vector3 u = {1.0f, 0.0f, 0.0f};
	Vector3 w = {0.0f, sinf(inc), cosf(inc)};
	Vector3 radial = scaleAndAdd(Vector3Scale(u, cosf(phi)), w, sinf(phi));
	Vector3 tangent = scaleAndAdd(Vector3Scale(u, -sinf(phi)), w, cosf(phi));

	float v = sqrtf(G * (P->mass + mass) / d);
	Vector3 pos = scaleAndAdd(P->position, radial, d);
	Vector3 vel = scaleAndAdd(P->velocity, tangent, v);
	ms_body(&planets[*n], label, pos, vel, radius, mass, c);
	(*n)++;
}

SimState solarsystem_moons(){
	// static: state.planets points at it, so it must outlive this function
	static Planet planets[MS_TOTAL];
	int n = 0;

	ms_body(&planets[n++], "Sun", (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f},
	        MS_SUN_RADIUS, MS_SUN_MASS, MS_COL_SUN);

	//                          label      a      angle  radius  mass
	ms_planet(planets, &n, "Mercury",  700.0f,   0.0f,  6.0f,     2.0f, MS_COL_MERCURY);
	ms_planet(planets, &n, "Venus",   1100.0f, 120.0f, 14.0f,    25.0f, MS_COL_VENUS);

	int earth = ms_planet(planets, &n, "Earth", 1600.0f, 40.0f, 18.0f, 4000.0f, MS_COL_EARTH);
	//                    parent  label    d      phase  incl  radius mass
	ms_moon(planets, &n, earth, "Moon",   45.0f,   0.0f, 5.0f, 5.0f, 50.0f, MS_COL_MOON);

	ms_planet(planets, &n, "Mars", 2200.0f, 250.0f, 9.0f, 300.0f, MS_COL_MARS);

	int jupiter = ms_planet(planets, &n, "Jupiter", 3200.0f, 170.0f, 30.0f, 25000.0f, MS_COL_JUPITER);
	ms_moon(planets, &n, jupiter, "Io",        65.0f,   0.0f, 0.0f, 5.0f, 30.0f, MS_COL_IO);
	ms_moon(planets, &n, jupiter, "Europa",    95.0f, 100.0f, 2.0f, 4.0f, 20.0f, MS_COL_EUROPA);
	ms_moon(planets, &n, jupiter, "Ganymede", 130.0f, 200.0f, 1.0f, 7.0f, 60.0f, MS_COL_GANYMEDE);
	ms_moon(planets, &n, jupiter, "Callisto", 175.0f, 300.0f, 3.0f, 6.0f, 45.0f, MS_COL_CALLISTO);

	int saturn = ms_planet(planets, &n, "Saturn", 4400.0f, 300.0f, 28.0f, 15000.0f, MS_COL_SATURN);
	ms_moon(planets, &n, saturn, "Titan", 120.0f, 60.0f, 10.0f, 6.0f, 40.0f, MS_COL_TITAN);

	ms_planet(planets, &n, "Uranus",  6200.0f,  80.0f, 16.0f,  900.0f, MS_COL_URANUS);
	ms_planet(planets, &n, "Neptune", 8000.0f, 210.0f, 15.0f, 1000.0f, MS_COL_NEPTUNE);

	// the planets all orbit the same way, so the Sun would slowly drift away.
	// give it the opposite of the total momentum so the system stays in place.
	Vector3 p = {0.0f, 0.0f, 0.0f};
	for (int i = 1; i < n; i++){
		p = scaleAndAdd(p, planets[i].velocity, planets[i].mass);
	}
	planets[0].velocity = scaleAndAdd((Vector3){0.0f, 0.0f, 0.0f}, p, -1.0f / MS_SUN_MASS);

	SimState state = {0};
	Camera3D camera = {
		.position = (Vector3){ 0.0f, 2500.0f, -5000.0f },
		.target = (Vector3){0.0f, 0.0f, 0.0f},
		.up = (Vector3){ 0.0f, 1.0f, 0.0f },
		.fovy = 45.0f,
		.projection = CAMERA_PERSPECTIVE
	};
	state.planet_num = n;
	state.planets = planets;
	state.camera = camera;
	state.isPaused = 0;
	state.cameraState = 0;

	return state;
}
