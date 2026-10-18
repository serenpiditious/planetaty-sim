#include "raylib.h"
#include "renderer.h"
#include "simulation.h"

int main(){
	int screenWidth = 720;
	int screenHeight = 480;
	InitWindow(screenWidth,screenHeight,"planets");
	SetTargetFPS(60);
	
	int deltaTime = GetFrameTime();

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
		
	Planet *planets = &earth;
	SimState state = {.planets = planets};

	while(!WindowShouldClose()){
		render(state);
	}	
			
	CloseWindow();
	


	return 0;
}
