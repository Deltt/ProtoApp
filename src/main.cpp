#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "ecs/draggable_rect.hpp"

Camera2D camera;
const Color BACKGROUND_COLOR {220, 220, 220 ,255};

bool shouldCanvasUpdate = true;
int canvas_updates = 0;


RenderTexture2D canvasTexture;
void InitializeCanvas(int screenWidth, int screenHeight)
{
    canvasTexture = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(canvasTexture);
    ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();
}

void ResizeCanvas(int newWidth, int newHeight)
{
    UnloadRenderTexture(canvasTexture);
    canvasTexture = LoadRenderTexture(newWidth, newHeight);
    shouldCanvasUpdate = true;
}

void UpdateCanvas(Camera2D& camera)
{
    if (shouldCanvasUpdate) {
        BeginTextureMode(canvasTexture);
        ClearBackground(BACKGROUND_COLOR);
        
        BeginMode2D(camera);
		DrawDraggableRects();
		
        EndMode2D();
        
        EndTextureMode();
        shouldCanvasUpdate = false;
    }

	canvas_updates++;
}

void DrawCanvas()
{
    BeginDrawing();
    DrawTextureRec(canvasTexture.texture, 
                   (Rectangle){0, 0, (float)canvasTexture.texture.width, -(float)canvasTexture.texture.height}, 
                   (Vector2){0, 0}, WHITE);
    
    // Optional: Draw UI elements that should always update (like cursor, selection handles, etc.)
    // DrawUI();
    
    EndDrawing();
}

void NavigateCanvas(Camera2D& camera)
{
	// Inputs
	float wheel_scroll = GetMouseWheelMove();
	bool wheel_pressed = IsMouseButtonDown(MOUSE_MIDDLE_BUTTON);
	Vector2 mouse_movement = GetMouseDelta();

	// Navigation Logic
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

void InitializeApp()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "ProtoApp");
	SetTargetFPS(144);
	MaximizeWindow();

	camera = { 0 };
	camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	draggable_rects.reserve(128);
	draggable_rects.push_back(DraggableRect());
	draggable_rects[0].rect.x = 500;
	draggable_rects.push_back(DraggableRect());
}

int main()
{
	InitializeApp();

	InitializeCanvas(GetScreenWidth(), GetScreenHeight());

	int lastScreenWidth = GetScreenWidth();
    int lastScreenHeight = GetScreenHeight();

    // Main Loop
    while (!WindowShouldClose())
    {
        // Handle window resize
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();
        if (currentWidth != lastScreenWidth || currentHeight != lastScreenHeight) {
            ResizeCanvas(currentWidth, currentHeight);
            camera.offset = (Vector2){ currentWidth / 2.0f, currentHeight / 2.0f };
            lastScreenWidth = currentWidth;
            lastScreenHeight = currentHeight;
        }

        // Canvas Navigation Handling (Zoom, Pan)
        NavigateCanvas(camera);

        // Update Canvas Texture (if needed)
        UpdateCanvas(camera);

        // Draw the cached canvas
        DrawCanvas();
    }

	UnloadRenderTexture(canvasTexture);
    CloseWindow();

    return 0;
}