#include "canvas_node.hpp"
#include "canvas_navigator.hpp"
#include "canvas_renderer.hpp"
#include <cstring>

CanvasNode::CanvasNode(float p_x, float p_y, float p_width, float p_height)
{
	rect.x = p_x;
	rect.y = p_y;
	rect.width = p_width;
	rect.height = p_height;
    strcpy(title, "Unnamed");
}

CanvasNode::CanvasNode(Rectangle p_rect) : rect(p_rect)
{
    strcpy(title, "Unnamed");
}

CanvasNode::CanvasNode(Rectangle p_rect, std::string p_title) : rect(p_rect)
{
    strcpy(title, p_title.c_str());
}

void CanvasNode::draw() const
{
	float zoom_modifier = CanvasNavigator::getInstance().zoom_modifier;
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, {255, 255, 255, 255});

	if(zoom_modifier < 3.0f) {
		DrawTextEx(CanvasRenderer::getInstance().font_pragmatica_10, title, {rect.x, rect.y - 10 * zoom_modifier}, 10 * zoom_modifier, 0, {80, 80, 80, 255});
	}
	else {
		DrawTextEx(CanvasRenderer::getInstance().font_pragmatica_10, "...", {rect.x, rect.y - 10 * zoom_modifier}, 10 * zoom_modifier, 0, {80, 80, 80, 255});
	}
	
}

int updateCanvasNodes(Vector2 p_mouse_world_position)
{
	return 0;
}