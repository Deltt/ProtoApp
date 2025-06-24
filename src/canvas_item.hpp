#pragma once
#ifndef CANVAS_ITEM_H
#define CANVAS_ITEM_H

#include "raylib.h"
#include <string>

struct CanvasItem
{
	CanvasItem(Rectangle p_bounding_box);
	CanvasItem(Rectangle p_bounding_box, std::string title);

	Rectangle bounding_box;
	Vector2 mouse_offset;
	char title[8];
    bool selected, dragging;

    void draw() const;
};

int updateCanvasItems(Vector2 p_mouse_world_position);

#endif