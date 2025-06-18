#include "draggable_rect.hpp"
#include <cstring>

std::vector<DraggableRect> draggable_rects;

DraggableRect::DraggableRect()
: rect({0, 0, 100, 100}), color({255, 0, 0, 255}),
corner_roundness(0), selected(false), dragging(false)
{
    strcpy(title, "Hello");
}

DraggableRect::DraggableRect(Rectangle& p_rect, Color p_color, short p_corner_roundness)
: rect(p_rect), color(p_color),
corner_roundness(p_corner_roundness), selected(false), dragging(false)
{
    strcpy(title, "Hello");
}

void DraggableRect::Draw() const
{
    DrawRectangleRounded(rect, static_cast<float>(corner_roundness) / 100, 8, {255, 255, 255, 255});
    DrawText(title, rect.x + 32.0f, rect.y - 16.0, 16, {0, 0, 0, 255});
}

void DraggableRect::CenterToOrigin()
{
    rect.x -= rect.width * 0.5f;
    rect.y -= rect.height * 0.5f;
}

//---

void DrawDraggableRects()
{
	for(int i = 0; i < draggable_rects.size(); i++)
	{
		draggable_rects[i].Draw();
	}
}