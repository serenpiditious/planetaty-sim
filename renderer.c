#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "./include/renderer.h"

// moves camera
void cam_update(Camera3D *camera){
    float del_theta = DELTA_THETA * DEG2RAD;
    Vector3 perp;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;
    Quaternion rotator;
    Vector3 cam_dir = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
    Vector3 cam_right = Vector3CrossProduct(cam_dir, camera->up);

    // rotations
    if (IsKeyDown(KEY_UP) || GetMouseDelta().y > 0) pitch -= del_theta;
    if (IsKeyDown(KEY_DOWN) || GetMouseDelta().y < 0) pitch += del_theta;
    if (IsKeyDown(KEY_RIGHT) || GetMouseDelta().x > 0) yaw -= del_theta;
    if (IsKeyDown(KEY_LEFT) || GetMouseDelta().x < 0) yaw += del_theta;
    if (IsKeyDown(KEY_E)) roll += del_theta;
    if (IsKeyDown(KEY_Q)) roll -= del_theta;

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

    rotator = QuaternionFromEuler(pitch, yaw, roll);
    cam_dir = Vector3RotateByQuaternion(cam_dir, rotator);
    camera->up = Vector3RotateByQuaternion(camera->up, rotator);
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

    BeginMode3D(state->camera);
        Planet *planet = state->planets;
        for (int i = 0; i < state->planet_num; i++){
            DrawSphereWires(planet->position, planet->radius, 23, 23, RED);
            planet += 1;
        }
    EndMode3D();
    EndDrawing();
}