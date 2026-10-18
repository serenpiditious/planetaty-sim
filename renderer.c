#pragma once
#include <raylib.h>
#include "renderer.h"

int render(SimState state){

	ClearBackground(BLACK);
	BeginDrawing();
		DrawRectangle(50,50,5,5,WHITE);	
	EndDrawing();	

	return 0;
}
