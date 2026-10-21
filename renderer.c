#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "./include/renderer.h"
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include "./include/raygui.h"

void drawTrail(Planet *planet){
	for(int i = 0; i < TRAIL_SIZE - 1; i++){
		DrawLine3D(planet->history[i], planet->history[i+1], planet->trailColor);
	}

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

	if (IsKeyDown(KEY_TAB)){
		change_pos /= 10;
	}

	del_theta = DELTA_THETA * DEG2RAD * state ->deltaTime;
	if (IsKeyDown(KEY_UP) || GetMouseDelta().y < 0) pitch += del_theta;
	if (IsKeyDown(KEY_DOWN) || GetMouseDelta().y > 0) pitch -= del_theta;
	if (IsKeyDown(KEY_RIGHT) || GetMouseDelta().x > 0) yaw -= del_theta;
	if (IsKeyDown(KEY_LEFT) || GetMouseDelta().x < 0) yaw += del_theta;
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
	if(!state->isPaused){
		cam_update(state);
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

	DrawCircleV(mousePos, 5, RED); 

	//gui starts here
	if(state->isPaused){
		EnableCursor();
		ShowCursor();

		float startX = 200.0f;
		float startY = 72.0f;
		float verticalSpacing = 80.0f; 

		float squareSize = 20.0f;
		float paddingBetween = 20.0f;  // Gap between the square and the text
		float buttonWidth = 500.0f;
		float buttonHeight = 20.0f;

		const char* buttonLabels[9] = {
			"Planet1", "Planet2", "Planet3", 
			"Planet4", "Planet5", "Planet6", 
			"Planet7", "Planet8", "Planet9"
		};

		for (int i = 0; i < 9; i++) 
		{
			float currentY = startY + (i * verticalSpacing);

			//Color indicatorColor = (state->activeButtonIndex == i) ? LIME : DARKGREEN;

			GuiDrawRectangle((Rectangle){ startX, currentY, squareSize, squareSize }, 0, BLANK, DARKGREEN);

			float buttonX = startX + squareSize + paddingBetween;

			if (GuiLabelButton((Rectangle){ buttonX, currentY, buttonWidth, buttonHeight }, buttonLabels[i])) 
			{
				state->activePlanetIndex = i;
				printf("%d",state->activePlanetIndex);
				//printf("Button %d is now active!\n", i + 1);
			}
		}
	}


	EndDrawing();
}
