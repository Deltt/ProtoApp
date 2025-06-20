#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "globals.hpp"

void initializeApp();
void initializeData();
void initializeWindow();


// -----------------------------------------------------------------------

int main()
{
	initializeApp();

    // Main Loop
    while (!WindowShouldClose())
    {
		CanvasNavigator::getInstance().process();
        CanvasRenderer::getInstance().process();
    }

	UnloadRenderTexture(CanvasRenderer::getInstance().canvas_texture);
    CloseWindow();

    return 0;
}

void initializeApp()
{
	initializeData();
	initializeWindow();
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
	ClearBackground(CanvasRenderer::getInstance().BACKGROUND_COLOR);
	SetTargetFPS(144);
	MaximizeWindow();
}