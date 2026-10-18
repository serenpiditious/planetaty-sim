#include "raylib.h"
#include "renderer.h"

void render(SimState state){
    ClearBackground(BLACK);

    BeginMode3D(state.camera);
        Planet *planet = state.planets;
        for (int i = 0; i < state.planet_num; i++){
            DrawSphereWires(planet -> position, planet -> radius, 25, 25, RED);
            planet += 1;
        }
    EndMode3D();
}
