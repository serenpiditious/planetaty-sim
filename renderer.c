#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "./include/renderer.h"

// moves camera
void cam_update(Camera3D *camera){
    float del_theta = DELTA_THETA * DEG_TO_RAD;
    Vector3 perp;
    Quaternion rotator = {1.0f, 0.0f, 0.0f, 0.0f};
    Quaternion del_rot;
    Vector3 cam_dir = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
    Vector3 cam_right = Vector3CrossProduct(cam_dir, camera->up);

    // movement
    Vector3 del_pos = {0.0f, 0.0f, 0.0f};
    if (IsKeyDown(KEY_W)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_dir, DELTA_POS));
    }
    if (IsKeyDown(KEY_S)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_dir, -DELTA_POS));
    }
    if (IsKeyDown(KEY_D)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_right, DELTA_POS));
    }
    if (IsKeyDown(KEY_A)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_right, -DELTA_POS));
    }
    if (IsKeyDown(KEY_SPACE)){
        del_pos = Vector3Add(del_pos, Vector3Scale(camera->up, DELTA_POS));
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)){
        del_pos = Vector3Add(del_pos, Vector3Scale(camera->up, -DELTA_POS));
    }
    camera->position = Vector3Add(camera->position, del_pos);
    camera->target = Vector3Add(camera->position, cam_dir);
}

// renders all planets
void render(SimState *state){
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(state->camera);
        Planet *planet = state->planets;
        for (int i = 0; i < state->planet_num; i++){
            DrawSphereWires(planet->position, planet->radius, 23, 23, RED);
            planet += 1;
        }
    EndMode3D();
    EndDrawing();
}