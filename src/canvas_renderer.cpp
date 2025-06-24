#include "canvas_renderer.hpp"
#include "canvas_navigator.hpp"
#include "data_manager.hpp"

CanvasRenderer::CanvasRenderer()
{
	int last_screen_width = GetScreenWidth();
    int last_screen_height = GetScreenHeight();
	
	loadFonts();
    canvas_texture = LoadRenderTexture(last_screen_width, last_screen_height);
	menu_texture = LoadRenderTexture(last_screen_width * 0.125f, last_screen_height);
	request_canvas_update = true;

    BeginTextureMode(canvas_texture);
    ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();
}

CanvasRenderer::~CanvasRenderer()
{
	UnloadRenderTexture(canvas_texture);
}

CanvasRenderer& CanvasRenderer::getInstance()
{
    static CanvasRenderer instance;
    return instance;
}

void CanvasRenderer::process()
{
	handleWindowResize(last_screen_width, last_screen_height);

	if (request_canvas_update) {
		updateCanvas(CanvasNavigator::getInstance().canvas_camera);
	}
	
	updateMenu();
	drawPass();
}

void CanvasRenderer::handleWindowResize(int& last_screen_width, int& last_screen_height)
{
	int current_width = GetScreenWidth();
	int current_height = GetScreenHeight();
	if (current_width != last_screen_width || current_height != last_screen_height) {
		resizeCanvas(current_width, current_height);
		CanvasNavigator::getInstance().canvas_camera.offset = (Vector2){ current_width / 2.0f, current_height / 2.0f };
		last_screen_width = current_width;
		last_screen_height = current_height;
	}
}

void CanvasRenderer::resizeCanvas(int resize_width, int resize_height)
{
    UnloadRenderTexture(canvas_texture);
    canvas_texture = LoadRenderTexture(resize_width, resize_height);
    request_canvas_update = true;
}

void CanvasRenderer::updateCanvas(Camera2D& camera)
{
	BeginTextureMode(canvas_texture);
	ClearBackground(BACKGROUND_COLOR);
	
	// Mode 2D (Camera transformations)
	BeginMode2D(camera);

	drawCanvasItems();
	DrawRectangle(-10, - 10, 20, 20, (Color){255, 0, 0, 255});
	
	EndMode2D();
	
	EndTextureMode();
	
	request_canvas_update = false;
	canvas_updates++;
}

void CanvasRenderer::updateMenu()
{
	BeginTextureMode(menu_texture);

	ClearBackground(BACKGROUND_COLOR);
	DrawRectangle(0, 0, menu_texture.texture.width, menu_texture.texture.height, (Color){50, 50, 50, 255});

	EndTextureMode();
}

void CanvasRenderer::drawPass()
{
    BeginDrawing();
    DrawTextureRec(canvas_texture.texture, 
                   (Rectangle){0, 0, (float)canvas_texture.texture.width, -(float)canvas_texture.texture.height}, 
                   (Vector2){0, 0}, WHITE);

	DrawTextureRec(menu_texture.texture, 
                   (Rectangle){0, 0, (float)menu_texture.texture.width, -(float)menu_texture.texture.height}, 
                   (Vector2){0, 0}, WHITE);

    // Optional: Draw UI elements that should always update (like cursor, selection handles, etc.)
    // DrawUI();
    
    EndDrawing();
}

void CanvasRenderer::loadFonts()
{
	font[0] = LoadFontEx("../fonts/Pragmatica.ttf", 10, 0, 95);
}

void CanvasRenderer::drawCanvasItems()
{
	for(int i = 0; i < DataManager::getInstance().getCanvasItems().size(); i++)
	{
		DataManager::getInstance().getCanvasItems()[i].draw();
	}
}