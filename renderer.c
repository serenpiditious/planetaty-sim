#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "./include/renderer.h"
#include "rlgl.h"

void drawTrail(Planet *planet){
          for(int i = 0; i < TRAIL_SIZE - 1; i++){
                 DrawLine3D(planet->history[i], planet->history[i+1], planet->trailColor);
          }

  }
//finds the closest one of cardinal direction and up and down
Vector3 closest_cardinal_dir(Vector3 unit_dir){
    unit_dir = Vector3Normalize(unit_dir);
    Vector3 cardinal_dirs[] = {(Vector3) {0.0f, 1.0f, 0.0f}, 
        (Vector3) {0.0f, -1.0f, 0.0f}, 
        (Vector3) {1.0f, 0.0f, 0.0f},
        (Vector3) {-1.0f, 0.0f, 0.0f},
        (Vector3) {0.0f, 0.0f, 1.0f},
        (Vector3) {0.0f, 0.0f, -1.0f}
    };

    float min_dist = 2;
    float dist;
    Vector3 min_vec = cardinal_dirs[0];
    for (int i = 1; i < 6; i++){
        dist = Vector3Distance(unit_dir, (cardinal_dirs[i]));
        if (dist < min_dist){
        min_dist = dist;
        min_vec = cardinal_dirs[i];
        }
    }
    return min_vec;
}

// moves camera
void cam_update(SimState *state){
    Camera3D *camera = &(state->camera);

    float del_theta;
    float change_pos = DELTA_POS * state ->deltaTime;
    Vector3 perp;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;
    Vector3 cam_dir = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
    Vector3 cam_right = Vector3CrossProduct(cam_dir, camera->up);

    del_theta = DELTA_THETA * DEG2RAD * state ->deltaTime;
    if (IsKeyDown(KEY_UP) || GetMouseDelta().y > 0) pitch += del_theta;
    if (IsKeyDown(KEY_DOWN) || GetMouseDelta().y < 0) pitch -= del_theta;
    if (IsKeyDown(KEY_RIGHT) || GetMouseDelta().x < 0) yaw -= del_theta;
    if (IsKeyDown(KEY_LEFT) || GetMouseDelta().x > 0) yaw += del_theta;
    if (IsKeyDown(KEY_E)) roll += del_theta;
    if (IsKeyDown(KEY_Q)) roll -= del_theta;

    // movement
    Vector3 del_pos = {0.0f, 0.0f, 0.0f};
    if (IsKeyDown(KEY_W)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_dir, change_pos));
    }
    if (IsKeyDown(KEY_S)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_dir, -change_pos));
    }
    if (IsKeyDown(KEY_D)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_right, change_pos));
    }
    if (IsKeyDown(KEY_A)){
        del_pos = Vector3Add(del_pos, Vector3Scale(cam_right, -change_pos));
    }
    if (IsKeyDown(KEY_SPACE)){
        del_pos = Vector3Add(del_pos, Vector3Scale(camera->up, change_pos));
    }
    if (IsKeyDown(KEY_LEFT_SHIFT)){
        del_pos = Vector3Add(del_pos, Vector3Scale(camera->up, -change_pos));
    }

    cam_dir = Vector3RotateByAxisAngle(cam_dir, camera->up, yaw);
    camera->up = Vector3RotateByAxisAngle(camera->up, cam_dir, roll);
    cam_dir = Vector3RotateByAxisAngle(cam_dir, cam_right, pitch);
    camera->up = Vector3RotateByAxisAngle(camera->up, cam_right, pitch);

    camera->position = Vector3Add(camera->position, del_pos);
    camera->target = Vector3Add(camera->position, cam_dir);

    if (IsKeyDown(KEY_R)) {
        camera->up = (Vector3) {0.0f, 1.0f, 0.0f};
        camera->target.z = 0.0f;
    }
}

// renders all planets
void render(SimState *state){
    BeginDrawing();
    ClearBackground(BLACK);

    cam_update(state);


    rlSetClipPlanes(0.01f,100000.0f);
    BeginMode3D(state->camera);
        Planet *planet = state->planets;
        for (int i = 0; i < state->planet_num; i++){
            DrawSphereWires(planet->position, planet->radius, 17, 17, state->planets[i].planetColor);
            drawTrail(state->planets + i);
            planet += 1;
        }
    EndMode3D();
    EndDrawing();
}
