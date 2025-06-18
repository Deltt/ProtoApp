//#include "../libs/raylib/include/raylib.h"
#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "ecs/components.hpp"

const Color BACKGROUND_COLOR {220, 220, 220 ,255};

bool shouldCanvasUpdate = true;

DraggableRect TestMovable({900, 500}, {600, 400});



void NavigateCanvas(Camera2D& camera)
{
	// Inputs
	float wheel_scroll = GetMouseWheelMove();
	bool wheel_pressed = IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
	Vector2 mouse_movement = GetMouseDelta();

	// Move Logic
	if (wheel_scroll != 0) {
		Vector2 mouseWorldPosBeforeZoom = GetScreenToWorld2D(GetMousePosition(), camera);

		camera.zoom += wheel_scroll * camera.zoom * 0.05f;
		if (camera.zoom < 0.1f) camera.zoom = 0.1f;
		if (camera.zoom > 5.0f) camera.zoom = 5.0f;

		Vector2 mouseWorldPosAfterZoom = GetScreenToWorld2D(GetMousePosition(), camera);

		camera.target.x += mouseWorldPosBeforeZoom.x - mouseWorldPosAfterZoom.x;
		camera.target.y += mouseWorldPosBeforeZoom.y - mouseWorldPosAfterZoom.y;
		shouldCanvasUpdate = true;
	}

	if(wheel_pressed) {
		camera.offset = Vector2Add(camera.offset, mouse_movement);
		shouldCanvasUpdate = true;
	}
}

void DrawCanvas(Camera2D& camera)
{
	BeginDrawing();

	ClearBackground(BACKGROUND_COLOR);

	if(shouldCanvasUpdate)
	{
		BeginMode2D(camera);
		TestMovable.Draw();
		EndMode2D();
	}
	else
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	EndDrawing();
	shouldCanvasUpdate = false;
}

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "Basic Raylib Window");
	SetTargetFPS(144);
	MaximizeWindow();

	Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 400, 300 };  // center of screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	TestMovable.CenterToOrigin();

    // Main Loop
    while (!WindowShouldClose())
    {
		// Canvas Navigation Handling (Zoom, Pan)
		NavigateCanvas(camera);

		// Draw
		DrawCanvas(camera);
    }

    CloseWindow();

    return 0;
}