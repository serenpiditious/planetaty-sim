#include "../include/simulation.h"

#define TRAIL_ALPHA 210

#define COL_SUN      255, 225,  80
#define COL_MERCURY    0, 255, 200
#define COL_VENUS    255,  90, 200
#define COL_EARTH     90, 160, 255
#define COL_MARS     255,  70,  90
#define COL_JUPITER  255, 150,  50
#define COL_SATURN   190, 110, 255
#define COL_URANUS    60, 230, 255
#define COL_NEPTUNE  110,  90, 255
SimState solarsystem(){
	Planet Sun = {.position = {0.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 0.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 350.0f,
		.mass = 20000000,
		.trailColor = {COL_SUN, TRAIL_ALPHA},
		.history = {0},
		.label = "SUN",
		.planetColor = {COL_SUN, 255}};
	Planet Mercury = {.position = {500.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 1900.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 10.0f,
		.mass = 3,
		.trailColor = {COL_MERCURY, TRAIL_ALPHA},
		.history = {0},
		.label = "MERCURY",
		.planetColor = {COL_MERCURY, 255}};
	Planet Venus = {.position = {750.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 1500.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 25.0f,
		.mass = 25,
		.trailColor = {COL_VENUS, TRAIL_ALPHA},
		.history = {0},
		.label = "VENUS",
		.planetColor = {COL_VENUS, 255}};
	Planet Earth = {.position = {1300.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 1050.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 50.0f,
		.mass = 30,
		.trailColor = {COL_EARTH, TRAIL_ALPHA},
		.history = {0},
		.label = "EARTH",
		.planetColor = {COL_EARTH, 255}};
	Planet Mars = {.position = {2000.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 800.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 10.0f,
		.mass = 3,
		.trailColor = {COL_MARS, TRAIL_ALPHA},
		.history = {0},
		.label = "MARS",
		.planetColor = {COL_MARS, 255}};
	Planet Jupiter = {.position = {3000.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 650.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 165,
		.mass = 6000,
		.trailColor = {COL_JUPITER, TRAIL_ALPHA},
		.history = {0},
		.label = "JUPITER",
		.planetColor = {COL_JUPITER, 255}};
	Planet Saturn = {.position = {4500.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 550.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 145,
		.mass = 3000,
		.trailColor = {COL_SATURN, TRAIL_ALPHA},
		.history = {0},
		.label = "SATURN",
		.planetColor = {COL_SATURN, 255}};
	Planet Uranus = {.position = {8000.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 400.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 65,
		.mass = 480,
		.trailColor = {COL_URANUS, TRAIL_ALPHA},
		.history = {0},
		.label = "URANUS",
		.planetColor = {COL_URANUS, 255}};
	Planet Neptune = {.position = {12500.0f, 0.0f, 0.0f},
		.velocity = {0.0f, 0.0f, 300.0f},
		.acceleration = {0.0f, 0.0f, 0.0f},
		.radius = 63,
		.mass = 500,
		.trailColor = {COL_NEPTUNE, TRAIL_ALPHA},
		.history = {0},
		.label = "NEPTUNE",
		.planetColor = {COL_NEPTUNE, 255}};

	Planet planets[] = {Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune};
	int planet_num = 9;
	SimState state = {0};
	Camera3D camera = {
		.position = (Vector3){ 0.0f, 0.0f, -500.0f },  // Camera position
		.target = (Vector3){0.0f, 0.0f, 0.0f},      // Camera looking at point
		.up = (Vector3){ 0.0f, 1.0f, 0.0f },          // Camera up vector (rotation towards target)
		.fovy = 45.0f,                                // Camera field-of-view Y
		.projection = CAMERA_PERSPECTIVE
	};
	state.planet_num = planet_num;
	state.planets = planets;
	state.camera = camera;
	state.isPaused = 0;
	state.cameraState = 0;


	return state;
}
