#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "./include/renderer.h"
#include "include/simulation.h"
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include "./include/raygui.h"
#define MOUSE_SENSITIVITY 0.0025f
#define OFFSET_VECTOR (Vector3){0.0f,1.0f,0.0f}
#define CAM_DIST 1.1f

//draws a fucking trail
void drawTrail(Planet *planet){
	for(int i = 0; i < TRAIL_SIZE - 1; i++){
		DrawLine3D(planet->history[(planet->HeadIndex + i)%TRAIL_SIZE], planet->history[(planet->HeadIndex + i+1)%TRAIL_SIZE], planet->trailColor);
	}

}
// moves camera
void fps_cam(SimState *state){
	Camera3D *camera = &(state->camera);

	Vector2 mouseDelta = GetMouseDelta();

	float del_theta;
	float change_pos = DELTA_POS * state ->deltaTime;
	Vector3 perp;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	Vector3 cam_dir = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
	Vector3 cam_right = Vector3CrossProduct(cam_dir, camera->up);

	yaw   -= mouseDelta.x * MOUSE_SENSITIVITY;
	pitch -= mouseDelta.y * MOUSE_SENSITIVITY;
	

	if (IsKeyDown(KEY_TAB)){
		change_pos /= 10;
	}

	del_theta = DELTA_THETA * DEG2RAD * state ->deltaTime;
	if (IsKeyDown(KEY_UP)) pitch += del_theta;
	if (IsKeyDown(KEY_DOWN)) pitch -= del_theta;
	if (IsKeyDown(KEY_RIGHT)) yaw -= del_theta;
	if (IsKeyDown(KEY_LEFT)) yaw += del_theta;
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

// camera targets the planet
void target_cam(SimState *state){
	Planet *planet = state->planets + state->activePlanetIndex;
	Vector3 relPos = Vector3Scale(Vector3Add(Vector3Normalize(planet->position), OFFSET_VECTOR), planet->radius * 7);
	state->camera.position = Vector3Add(relPos,planet->position);
	//Vector3Add(Vector3Scale(OFFSET_VECTOR, planet->radius), planet->position)
	state->camera.target = planet->position;
	state->camera.up = Vector3Add(Vector3Normalize(planet->velocity),OFFSET_VECTOR);
}

// renders all planets
void render(SimState *state){
	if(!state->isPaused && state->cameraState==0){
		fps_cam(state);
	}else if (state->cameraState==1){
		target_cam(state);
	}
	if(IsKeyPressed(KEY_F)){
		state->cameraState = 0;
	}
	BeginDrawing();
	ClearBackground(BLACK);

	rlSetClipPlanes(0.01f,100000.0f);
	BeginMode3D(state->camera);
	Planet *planet = state->planets;
	for (int i = 0; i < state->planet_num; i++){
		DrawSphereWires(planet->position, planet->radius, 17, 17, state->planets[i].planetColor);
		drawTrail(state->planets + i);
		planet += 1;
	}
	EndMode3D();
	//some debug info
	Vector2 mousePos = GetMousePosition();
	bool isLeftClickPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	bool isCursorHidden = IsCursorHidden();

	DrawRectangle(0, 0, GetScreenWidth(), 25, Fade(BLACK, 0.6f));

	DrawText(TextFormat("Mouse: X:%.0f Y:%.0f", mousePos.x, mousePos.y), 10, 5, 16, GREEN);
	DrawText(TextFormat("Click: %s", isLeftClickPressed ? "YES" : "NO"), 220, 5, 16, GREEN);
	DrawText(TextFormat("Cursor Hidden: %s", isCursorHidden ? "YES" : "NO"), 350, 5, 16, GREEN);
	DrawText(TextFormat("CAMERA STATE:  %d", state->cameraState), 550, 5, 16, GREEN);
	DrawText(TextFormat("FPS:  %d", GetFPS()), 800, 5, 16, GREEN);
	

	DrawCircleV(mousePos, 5, RED); 

	//gui starts here
	if(state->isPaused){

		float startX = 200.0f;
		float startY = 72.0f;
		float verticalSpacing = 80.0f; 

		float squareSize = 20.0f;
		float paddingBetween = 20.0f;  // Gap between the square and the text
		float buttonWidth = 500.0f;
		float buttonHeight = 36.0f;

		const char* buttonLabels[9] = {
			"SUN", "MERCURY", "VENUS", 
			"erth", "MARS", "JUPITER", 
			"SATRUN", "UR ANUS", "NEPCHUNE"
		};

		for (int i = 0; i < 9; i++) 
		{
			float currentY = startY + (i * verticalSpacing);

			//Color indicatorColor = (state->activeButtonIndex == i) ? LIME : DARKGREEN;

			GuiDrawRectangle((Rectangle){ startX, currentY, squareSize, squareSize }, 0, BLANK, DARKGREEN);

			float buttonX = startX + squareSize + paddingBetween;

			if (GuiLabelButton((Rectangle){ buttonX, currentY, buttonWidth, buttonHeight }, buttonLabels[i])) 
			{
				state->cameraState = 1;
				state->activePlanetIndex = i;
				printf("%d",state->activePlanetIndex);
				//printf("Button %d is now active!\n", i + 1);
			}
		}
	}


	EndDrawing();
}
