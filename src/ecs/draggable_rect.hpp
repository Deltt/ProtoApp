#pragma once
#include "raylib.h"
#include <vector>

struct DraggableRect;
extern std::vector<DraggableRect> draggable_rects;

struct DraggableRect {
	Rectangle rect;
	char title[8];
    Color color;
	short corner_roundness;
    bool selected, dragging;

	DraggableRect();
    DraggableRect(Rectangle& p_rect, Color p_color = {255, 255, 255, 255}, short p_corner_roundness = 0);

    void Draw() const;
    void CenterToOrigin();
};

void DrawDraggableRects();