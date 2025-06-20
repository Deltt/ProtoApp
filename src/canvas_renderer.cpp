#include "canvas_renderer.hpp"


//CanvasRenderer::CanvasRenderer() = default;
CanvasRenderer::CanvasRenderer()
{
	int last_screen_width = GetScreenWidth();
    int last_screen_height = GetScreenHeight();
	
	loadFonts();
    canvas_texture = LoadRenderTexture(last_screen_width, last_screen_height);

    BeginTextureMode(canvas_texture);
    ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();
}

CanvasRenderer::~CanvasRenderer() = default;

CanvasRenderer& CanvasRenderer::getInstance() {
    static CanvasRenderer instance;
    return instance;
}

void CanvasRenderer::process()
{
	handleWindowResize(last_screen_width, last_screen_height);
	updateCanvas(CanvasNavigator::getInstance().canvas_camera);
	drawCanvas();
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
    CanvasNavigator::getInstance().request_canvas_update = true;
}

void CanvasRenderer::updateCanvas(Camera2D& camera)
{
    if (CanvasNavigator::getInstance().request_canvas_update) {
        BeginTextureMode(canvas_texture);
        ClearBackground(BACKGROUND_COLOR);
        
		// Mode 2D (Camera transformations)
        BeginMode2D(camera);

		drawCanvasItems();
		DrawRectangle(-10, - 10, 20, 20, (Color){255, 0, 0, 255});
		
        EndMode2D();
        
        EndTextureMode();
        CanvasNavigator::getInstance().request_canvas_update = false;
    }

	canvas_updates++;
}

void CanvasRenderer::drawCanvas()
{
    BeginDrawing();
    DrawTextureRec(canvas_texture.texture, 
                   (Rectangle){0, 0, (float)canvas_texture.texture.width, -(float)canvas_texture.texture.height}, 
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
	for(int i = 0; i < canvas_items.size(); i++)
	{
		canvas_items[i].draw();
	}
}