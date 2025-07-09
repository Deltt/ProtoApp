#include "canvas_renderer.hpp"
#include "canvas_navigator.hpp"
#include "data_manager.hpp"

CanvasRenderer::CanvasRenderer()
{
	int last_screen_width = GetScreenWidth();
    int last_screen_height = GetScreenHeight();
	drawn_elements = 0;
	
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

	// Actual texture drawing
	drawPass();
}

void CanvasRenderer::handleWindowResize(int& p_last_screen_width, int& p_last_screen_height)
{
	int current_width = GetScreenWidth();
	int current_height = GetScreenHeight();
	if (current_width != p_last_screen_width || current_height != p_last_screen_height)
	{
		resizeCanvas(current_width, current_height);
		CanvasNavigator::getInstance().canvas_camera.offset = (Vector2){ current_width / 2.0f, current_height / 2.0f };
		p_last_screen_width = current_width;
		p_last_screen_height = current_height;
	}
}

void CanvasRenderer::resizeCanvas(int p_resize_width, int p_resize_height)
{
    UnloadRenderTexture(canvas_texture);
    canvas_texture = LoadRenderTexture(p_resize_width, p_resize_height);
    request_canvas_update = true;
}

void CanvasRenderer::updateCanvas(Camera2D& p_camera)
{
	BeginTextureMode(canvas_texture);
	ClearBackground(BACKGROUND_COLOR);
	
	// Mode 2D (Camera transformations)
	BeginMode2D(p_camera);

	drawCanvasNodes();
	DrawRectangle(-10, - 10, 20, 20, (Color){255, 0, 0, 255}); // Debug Red Center Rect
	
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

	drawDebugInfo();

	EndTextureMode();
}

void CanvasRenderer::drawDebugInfo()
{
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "Debug\nDrawn elements: %d\n", drawn_elements);
	DrawTextEx(font_pragmatica_20, buffer, {5, 10}, 20, 0, {255, 0, 0, 255});
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
	font_pragmatica_10 = LoadFontEx("../fonts/Pragmatica.ttf", 10, NULL, 0);
	font_pragmatica_20 = LoadFontEx("../fonts/Pragmatica.ttf", 20, NULL, 0);
}

void CanvasRenderer::drawCanvasNodes()
{
	Vector2 top_left {GetScreenToWorld2D((Vector2){0, 0}, CanvasNavigator::getInstance().canvas_camera)};
	Vector2 bottomRight {GetScreenToWorld2D((Vector2){static_cast<float>(last_screen_width), static_cast<float>(last_screen_height)}, CanvasNavigator::getInstance().canvas_camera)};
	Box query_box{ {top_left.x + menu_texture.texture.width * CanvasNavigator::getInstance().zoom_modifier, top_left.y}, {bottomRight.x, bottomRight.y} };
	std::vector<Entry> result_s;

	DataManager::getInstance().getTree().query(boost::geometry::index::intersects(query_box), std::back_inserter(result_s));
	drawn_elements = result_s.size();

	for (const auto& v : result_s)
	{
    	size_t object_index = v.second;
		DataManager::getInstance().getCanvasNodes()[object_index].value().draw();
	}
}