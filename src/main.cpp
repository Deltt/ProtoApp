#include "canvas_renderer.hpp"
#include "canvas_navigator.hpp"
#include "canvas_item.hpp"
#include "data_manager.hpp"


void initializeWindow();


// -----------------------------------------------------------------------

int main()
{
	initializeWindow();

    // Main Loop
    while (!WindowShouldClose())
    {
		CanvasNavigator::getInstance().process();
        CanvasRenderer::getInstance().process();
    }
	
    CloseWindow();

    return 0;
}

void initializeWindow()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "ProtoApp");
	ClearBackground(CanvasRenderer::getInstance().BACKGROUND_COLOR);
	SetTargetFPS(144);
	MaximizeWindow();
}