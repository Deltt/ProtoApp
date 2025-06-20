#include "canvas_item.hpp"
#include <cstring>

std::vector<CanvasItem> canvas_items;

CanvasItem::CanvasItem(Rectangle p_bounding_box) : bounding_box(p_bounding_box)
{
    strcpy(title, "Unnamed");
}

CanvasItem::CanvasItem(Rectangle p_bounding_box, std::string p_title) : bounding_box(p_bounding_box)
{
    strcpy(title, p_title.c_str());
}

void CanvasItem::draw() const
{
	float zoom_modifier = CanvasNavigator::getInstance().zoom_modifier;
    DrawRectangle(bounding_box.x, bounding_box.y, bounding_box.width, bounding_box.height, {255, 255, 255, 255});

	if(zoom_modifier < 3.0f) {
		DrawTextEx(CanvasRenderer::getInstance().font[0], title, {bounding_box.x, bounding_box.y - 10 * zoom_modifier}, 10 * zoom_modifier, 0, {80, 80, 80, 255});
	}
	else {
		DrawTextEx(CanvasRenderer::getInstance().font[0], "...", {bounding_box.x, bounding_box.y - 10 * zoom_modifier}, 10 * zoom_modifier, 0, {80, 80, 80, 255});
	}
	
}

int updateCanvasItems(Vector2 p_mouse_world_position)
{
	return 0;
}