#include <raylib.h>
#include "./include/renderer.h"

// renders all planets
void render(SimState state){
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(state.camera);
        Planet *planet = state.planets;
        for (int i = 0; i < state.planet_num; i++){
            DrawSphereWires(planet -> position, planet -> radius, 23, 23, RED);
            planet += 1;
        }
    EndMode3D();
    EndDrawing();
}