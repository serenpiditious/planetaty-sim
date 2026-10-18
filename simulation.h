#pragma once

#include <math.h>
#include "raylib.h"

#define G 6.67 x pow(10, -`11)

typedef struct{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float radius;
	float mass;
} Planet;

typedef struct{
    int planet_num;
    Planet *planets;
    float deltaTime;
    Camera3D camera;
} SimState;
