#pragma once
#ifndef CANVAS_NODE_H
#define CANVAS_NODE_H

#include "raylib.h"
#include <string>

struct CanvasNode
{
	CanvasNode(float x, float y, float width, float height);
	CanvasNode(Rectangle p_rect);
	CanvasNode(Rectangle p_rect, std::string p_title);

	Rectangle rect;
	Vector2 mouse_offset;
	char title[8];
    bool selected, dragging;

    void draw() const;
};

int updateCanvasNodes(Vector2 p_mouse_world_position);

#endif