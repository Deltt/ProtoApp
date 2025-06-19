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
    DrawRectangle(bounding_box.x, bounding_box.y, bounding_box.width, bounding_box.height, {255, 255, 255, 255});
    DrawText(title, bounding_box.x + 32.0f, bounding_box.y - 16.0, 16, {0, 0, 0, 255});
}

int updateCanvasItems(Vector2 p_mouse_world_position)
{
	return 0;
}

void drawCanvasItems()
{
	for(int i = 0; i < canvas_items.size(); i++)
	{
		canvas_items[i].draw();
	}
}