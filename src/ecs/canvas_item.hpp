#pragma once
#include "raylib.h"
#include <vector>
#include <string>

struct CanvasItem;
extern std::vector<CanvasItem> canvas_items;

struct CanvasItem {
	Rectangle bounding_box;
	Vector2 mouse_offset;
	char title[8];
    bool selected, dragging;

	CanvasItem(Rectangle p_bounding_box);
	CanvasItem(Rectangle p_bounding_box, std::string title);

    void draw() const;
};

int updateCanvasItems(Vector2 p_mouse_world_position);
void drawCanvasItems();