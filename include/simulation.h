#pragma once

#include <math.h>
#include <raylib.h>

#define G 100
#define K 50 // repulsion b/w overlapping planets
#define TRAIL_SIZE 500


typedef struct{
          Vector3 position;
          Vector3 velocity;
          Vector3 acceleration;
          float radius;
          float mass;
          Color trailColor;
          Color planetColor;
          Vector3 history[TRAIL_SIZE];
	  int HeadIndex; //head of the trail
	  // using integer as boolean
	  int isStationary;
  } Planet;

typedef struct{
    int planet_num;
    Planet *planets;
    float deltaTime;
    Camera3D camera;
    int cameraState;
    int isPaused;
    int activePlanetIndex;
} SimState;

Vector3 scaleAndAdd(Vector3 vec, Vector3 dir, float scale);
float collision_vel(float u_pro, float u_bono, float mass_pro, float mass_bono, float e);
void update_acc(Planet* planet_ptr, Planet* planets, int planet_num);
void update_pos_vel(Planet* planet_ptr, float deltaTime);
void collision(Planet *pro, Planet *bono, float e);

void physics(SimState *state, float e);
