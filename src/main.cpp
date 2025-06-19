#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "canvas_item.hpp"
#include "canvas_navigator.hpp"

CanvasNavigator& canvas_navigator {CanvasNavigator::getInstance()};
const Color BACKGROUND_COLOR {220, 220, 220 ,255};
bool shouldCanvasUpdate {true};
int canvas_updates {0};
RenderTexture2D canvasTexture;

void initializeApp();
void initializeCanvas(int screenWidth, int screenHeight);
void resizeCanvas(int newWidth, int newHeight);
void updateCanvas(Camera2D& camera);
void drawCanvas();


// -----------------------------------------------------------------------

int main()
{
	initializeApp();

	initializeCanvas(GetScreenWidth(), GetScreenHeight());

	int lastScreenWidth = GetScreenWidth();
    int lastScreenHeight = GetScreenHeight();

    // Main Loop
    while (!WindowShouldClose())
    {
        // Handle window resize
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();
        if (currentWidth != lastScreenWidth || currentHeight != lastScreenHeight) {
            resizeCanvas(currentWidth, currentHeight);
            canvas_navigator.canvas_camera.offset = (Vector2){ currentWidth / 2.0f, currentHeight / 2.0f };
            lastScreenWidth = currentWidth;
            lastScreenHeight = currentHeight;
        }

        // Canvas Navigation Handling (Zoom, Pan)
		canvas_navigator.navigate();

        // Update Canvas Texture (if needed)
        updateCanvas(canvas_navigator.canvas_camera);

        // Draw the cached canvas
        drawCanvas();
    }

	UnloadRenderTexture(canvasTexture);
    CloseWindow();

    return 0;
}

void initializeApp()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "ProtoApp");
	SetTargetFPS(144);
	MaximizeWindow();

	canvas_navigator.loadFonts();

	canvas_items.reserve(128);
	canvas_items.push_back(CanvasItem({0, 0, 400, 200}));
}

void initializeCanvas(int screenWidth, int screenHeight)
{
    canvasTexture = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(canvasTexture);
    ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();
}

void resizeCanvas(int newWidth, int newHeight)
{
    UnloadRenderTexture(canvasTexture);
    canvasTexture = LoadRenderTexture(newWidth, newHeight);
    shouldCanvasUpdate = true;
}

void updateCanvas(Camera2D& camera)
{
    if (canvas_navigator.request_canvas_update) {
        BeginTextureMode(canvasTexture);
        ClearBackground(BACKGROUND_COLOR);
        
		// Mode 2D (Camera transformations)
        BeginMode2D(camera);

		drawCanvasItems();
		DrawRectangle(-10, - 10, 20, 20, (Color){255, 0, 0, 255});
		
        EndMode2D();
        
        EndTextureMode();
        canvas_navigator.request_canvas_update = false;
    }

	canvas_updates++;
}

void drawCanvas()
{
    BeginDrawing();
    DrawTextureRec(canvasTexture.texture, 
                   (Rectangle){0, 0, (float)canvasTexture.texture.width, -(float)canvasTexture.texture.height}, 
                   (Vector2){0, 0}, WHITE);
    
    // Optional: Draw UI elements that should always update (like cursor, selection handles, etc.)
    // DrawUI();
    
    EndDrawing();
}