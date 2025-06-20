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
RenderTexture2D canvas_texture;
int canvas_updates {0};

void initializeApp();
void initializeData();
void initializeWindow();
void initializeCanvas(int screen_width, int screen_height);
void handleWindowResize(int& last_screen_width, int& last_screen_height);
void resizeCanvas(int resize_width, int resize_height);
void updateCanvas(Camera2D& camera);
void drawCanvas();


// -----------------------------------------------------------------------

int main()
{
	initializeApp();

	int last_screen_width = GetScreenWidth();
    int last_screen_height = GetScreenHeight();

    // Main Loop
    while (!WindowShouldClose())
    {
		handleWindowResize(last_screen_width, last_screen_height);

		canvas_navigator.navigate();

        updateCanvas(canvas_navigator.canvas_camera);

        drawCanvas();
    }

	UnloadRenderTexture(canvas_texture);
    CloseWindow();

    return 0;
}

void initializeApp()
{
	initializeData();
	initializeWindow();
	initializeCanvas(GetScreenWidth(), GetScreenHeight());
}

void initializeData()
{
	canvas_items.reserve(128);
	canvas_items.push_back(CanvasItem({0, 0, 400, 200}));
}

void initializeWindow()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "ProtoApp");
	ClearBackground(BACKGROUND_COLOR);
	SetTargetFPS(144);
	MaximizeWindow();
}

void initializeCanvas(int screen_width, int screen_height)
{
	canvas_navigator.loadFonts();
    canvas_texture = LoadRenderTexture(screen_width, screen_height);

    BeginTextureMode(canvas_texture);
    ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();
}

void handleWindowResize(int& last_screen_width, int& last_screen_height)
{
	int current_width = GetScreenWidth();
	int current_height = GetScreenHeight();
	if (current_width != last_screen_width || current_height != last_screen_height) {
		resizeCanvas(current_width, current_height);
		canvas_navigator.canvas_camera.offset = (Vector2){ current_width / 2.0f, current_height / 2.0f };
		last_screen_width = current_width;
		last_screen_height = current_height;
	}
}

void resizeCanvas(int resize_width, int resize_height)
{
    UnloadRenderTexture(canvas_texture);
    canvas_texture = LoadRenderTexture(resize_width, resize_height);
    canvas_navigator.request_canvas_update = true;
}

void updateCanvas(Camera2D& camera)
{
    if (canvas_navigator.request_canvas_update) {
        BeginTextureMode(canvas_texture);
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
    DrawTextureRec(canvas_texture.texture, 
                   (Rectangle){0, 0, (float)canvas_texture.texture.width, -(float)canvas_texture.texture.height}, 
                   (Vector2){0, 0}, WHITE);
    
    // Optional: Draw UI elements that should always update (like cursor, selection handles, etc.)
    // DrawUI();
    
    EndDrawing();
}