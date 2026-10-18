#include <stdio.h>
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

int main(){
	Planet earth = {.position = {100.0f, 50.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 20.0f,
		.mass = 10000};
	Planet jupiter = {.position = {250.0f, 0.0f, 120.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 60.0f,
		.mass = 15000};
	Planet eridani = {.position = {0.0f, 700.0f, 60.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 20.0f,
		.mass = 100000};
	
	int planet_num = 3;
	Planet plan_list[] = {earth, jupiter, eridani};
	
	const int win_width = 1500;
	const int win_height = 700;

	Vector3 cen = {win_width/2, win_height/2, 0};

	Camera3D camera = {
		.position = (Vector3){ -30.0f, -30.0f, -30.0f },  // Camera position
    	.target = (Vector3)cen,      // Camera looking at point
    	.up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
    	.fovy = 45.0f,                                // Camera field-of-view Y
    	.projection = CAMERA_PERSPECTIVE
	};

	InitWindow(win_width, win_height, "Planetary Sim");

	SetTargetFPS(20);

	while (!WindowShouldClose()){
		float deltaTime = GetFrameTime();

		BeginDrawing();

			ClearBackground(WHITE);

			BeginMode3D(camera);

				for (int i = 0; i < planet_num; i++){
					DrawSphereWires(plan_list[i].position, plan_list[i]. radius, 25, 25, RED);
				}

			EndMode3D();

		EndDrawing();
	}
}
